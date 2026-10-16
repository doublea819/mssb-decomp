# Career menu button words

The main menu's button words are pictures (bank 6 textures 49, 52-57: 156x21 C4 with a shared
IA8 palette). `gen_labels.py` cuts their letters along the font's slant and assembles the
Career menu's words into pictures of the same size, format and palette
(`port/game/career_labels.c`). Letters available: C E F G M O P R T, a b c d e g h i l m n o p r s t x y
(no u; see compose.py PICK for the instance used per letter).

Run from the decomp root after one game run has written `build/port/bankdump/bank_06.bin`:

    python3 docs/career/tools/gen_labels.py

`gxdec.py bank.bin outdir prefix` decodes every texture of a bank to PNG.
