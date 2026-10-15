#!/usr/bin/env python3
"""Turn the web build's bundled pipeline list (port/web/initial_pipeline_cache.bin.gz)
into the native seed aurora looks for next to the executable
(build/port/initial_pipeline_cache.db). Native runs then compile every known
GPU pipeline in the background at boot instead of skipping draws the first time
an effect appears (the stutter / missing pieces on a fresh Mac).

Usage: python3 port/tools/native_pipeline_seed.py [out.db]
"""
import gzip, os, sqlite3, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, 'port', 'web', 'initial_pipeline_cache.bin.gz')
OUT = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'build', 'port', 'initial_pipeline_cache.db')
MAGIC, SCHEMA = 0x43505541, 1

try:
    import xxhash
    def h(cfg, typ):  # aurora: xxh3_hash(config, seed = shader type)
        return xxhash.xxh3_64_intdigest(cfg, seed=typ)
except ImportError:
    import hashlib
    def h(cfg, typ):  # only the (type, hash) key must be unique; aurora rehashes on load
        return int.from_bytes(hashlib.blake2b(bytes([typ]) + cfg, digest_size=8).digest(), 'little')

data = gzip.open(SRC).read()
magic, schema = struct.unpack_from('<II', data, 0)
if magic != MAGIC or schema != SCHEMA:
    sys.exit(f'unexpected seed header {magic:#x}/{schema}')

rows, pos = {}, 8
while pos + 16 <= len(data):
    typ, ver, size, first = struct.unpack_from('<B3xIII', data, pos)
    pos += 16
    cfg = data[pos:pos + size]
    pos += size
    if len(cfg) != size:
        break
    hv = h(cfg, typ)
    if hv >= 1 << 63:
        hv -= 1 << 64  # sqlite INTEGER is signed 64-bit
    rows[(typ, hv)] = (typ, hv, ver, size, cfg, first)

os.makedirs(os.path.dirname(OUT), exist_ok=True)
if os.path.exists(OUT):
    os.remove(OUT)
db = sqlite3.connect(OUT)
db.executescript(f'''
CREATE TABLE aurora_schema(value INTEGER);
INSERT INTO aurora_schema VALUES ({SCHEMA});
CREATE TABLE pipeline_cache (
  type INTEGER NOT NULL, hash INTEGER NOT NULL, config_version INTEGER NOT NULL,
  config_size INTEGER NOT NULL, config BLOB NOT NULL, first_frame_used INTEGER NOT NULL,
  PRIMARY KEY (type, hash));
CREATE INDEX pipeline_cache_load_order_idx ON pipeline_cache(type, config_version, first_frame_used);
''')
db.executemany('INSERT INTO pipeline_cache VALUES (?,?,?,?,?,?)', rows.values())
db.commit(); db.close()
print(f'{len(rows)} pipelines -> {OUT}')
