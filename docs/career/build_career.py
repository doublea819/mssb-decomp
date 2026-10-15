import os,re,json
R=os.path.expanduser('~/mnt/MarioSuperstarBaseballCareer/decomp')
H=os.path.expanduser('~/sp')
names=[re.search(r'CHAR_ID_(\w+)',l).group(1) for l in open(R+'/include/mssbTypes.h').read().split('\n')[79:133]]
pretty={'MARIO':'Mario','LUIGI':'Luigi','DK':'Donkey Kong','DIDDY':'Diddy Kong','PEACH':'Peach','DAISY':'Daisy','YOSHI':'Yoshi','BABYMARIO':'Baby Mario','BABYLUIGI':'Baby Luigi','BOWSER':'Bowser','WARIO':'Wario','WALUIGI':'Waluigi','KOOPA_GREEN':'Koopa Troopa (Green)','TOAD_RED':'Toad (Red)','BOO':'Boo','TOADETTE':'Toadette','SHYGUY_RED':'Shy Guy (Red)','BIRDO':'Birdo','MONTY':'Monty Mole','BOWSERJR':'Bowser Jr.','PARATROOPA_RED':'Paratroopa (Red)','PIANTA_BLUE':'Pianta (Blue)','PIANTA_RED':'Pianta (Red)','PIANTA_YELLOW':'Pianta (Yellow)','NOKI_BLUE':'Noki (Blue)','NOKI_RED':'Noki (Red)','NOKI_GREEN':'Noki (Green)','BRO_HAMMER':'Hammer Bro','TOADSWORTH':'Toadsworth','TOAD_BLUE':'Toad (Blue)','TOAD_YELLOW':'Toad (Yellow)','TOAD_GREEN':'Toad (Green)','TOAD_PURPLE':'Toad (Purple)','MAGIKOOPA_BLUE':'Magikoopa (Blue)','MAGIKOOPA_RED':'Magikoopa (Red)','MAGIKOOPA_GREEN':'Magikoopa (Green)','MAGIKOOPA_YELLOW':'Magikoopa (Yellow)','KINGBOO':'King Boo','PETEY':'Petey Piranha','DIXIE':'Dixie Kong','GOOMBA':'Goomba','PARAGOOMBA':'Paragoomba','KOOPA_RED':'Koopa Troopa (Red)','PARATROOPA_GREEN':'Paratroopa (Green)','SHYGUY_BLUE':'Shy Guy (Blue)','SHYGUY_YELLOW':'Shy Guy (Yellow)','SHYGUY_GREEN':'Shy Guy (Green)','SHYGUY_BLACK':'Shy Guy (Black)','DRYBONES_GRAY':'Dry Bones (Gray)','DRYBONES_GREEN':'Dry Bones (Green)','DRYBONES_RED':'Dry Bones (Red)','DRYBONES_BLUE':'Dry Bones (Blue)','BRO_FIRE':'Fire Bro','BRO_BOOMERANG':'Boomerang Bro'}
caps=['MARIO','PEACH','WARIO','DK','YOSHI','BOWSER']
cls=['PRIMARY_CAPTAIN','SECONDARY_CAPTAIN','UNIQUE_NON_CAPTAIN','PRIMARY_VARIANT','SECONDARY_VARIANT']
# lbl_801094E4
L=open(R+'/src/main/file_80069BDC.c').read().split('\n')
st=next(i for i,l in enumerate(L) if l.startswith('u8 lbl_801094E4[1540]'))
vals=[];lines=[];i=st+1
while not L[i].startswith('};'):
    for x in L[i].split(','):
        if x.strip(): vals.append(int(x)); lines.append(i+1)
    i+=1
# CharTableEntry
D=open(R+'/src/main/data_800E8300.c').read().split('\n')
ct0=next(i for i,l in enumerate(D) if l.startswith('CharTableEntry lbl_800E8558[54]'))
ct=[]
for k in range(54):
    nums=[int(x) for x in re.findall(r'\d+',D[ct0+1+k])]
    ct.append(dict(line=ct0+2+k,group=nums[0],base_id=nums[1],model_row=nums[2],is_base=nums[3],captain_flag=nums[4],variant_index=nums[5]))
gnames={1:'Koopa Troopa',2:'Toad',3:'Shy Guy',4:'Paratroopa',5:'Pianta',6:'Noki',7:'Bros',8:'Magikoopa',9:'Dry Bones'}
d=open(H+'/charstats.bin','rb').read()
FA=['WALL_SPLAT','WALL_JUMP','CLAMBER','SLIDING_CATCH','LASER','QUICK_THROW','SUPER_JUMP','MAGICAL_CATCH','TONGUE_CATCH','SUCTION','SUPER_CATCH','BALL_DASH','BODY_CHECK','SUPER_CURVE','UNASSIGNED','UNASSIGNED2']
CC=['BALANCED','POWER','SPEED','TECHNIQUE']
chars=[]
for c in range(54):
    r=d[c*0xA0:c*0xA0+0x3B]; t=vals[c*28:c*28+28]
    fs=int.from_bytes(r[0x20:0x24],'big')
    s=dict(CurveBallSpeed=r[0],FastBallSpeed=r[1],cursedBall=r[2],Curve=r[3],curveControl=r[4],
      FieldingStats=fs,FieldingAbilities=[FA[b] for b in range(16) if fs>>b&1],CharID=int.from_bytes(r[0x24:0x26],'big'),
      FieldingArm=r[0x26],BattingStance=r[0x27],SlapContactSize=r[0x28],ChargeContactSize=r[0x29],SlapHitPower=r[0x2A],
      ChargeHitPower=r[0x2B],BuntingContactSize=r[0x2C],HitTrajectoryPushPull=r[0x2D],HitTrajectoryHighLow=r[0x2E],
      Speed=r[0x2F],ThrowingArm=r[0x30],CharacterClass=CC[r[0x31]],Weight=r[0x32],Captain=r[0x33],CaptainStarHitPitch=r[0x34],
      NonCaptainStarSwing=r[0x35],NonCaptainStarPitch=r[0x36],BattingStatBar=r[0x37],PitchingStatBar=r[0x38],RunningStatBar=r[0x39],FieldingStatBar=r[0x3A])
    assert s['CharID']==c
    bars=dict(Batting=r[0x37],Pitching=r[0x38],Fielding=r[0x3A],Speed=r[0x39]); bars['Total']=sum(bars.values())
    chars.append(dict(id=c,enum='CHAR_ID_'+names[c],name=pretty[names[c]],
      challenge=dict(captain=caps[t[0]],variantClassification=cls[t[1]],raw=t[:4],scoutTable=t[4:],source='src/main/file_80069BDC.c:%d (lbl_801094E4 record %d, bytes %d..%d)'%(lines[c*28],c,c*28,c*28+27)),
      charTable=dict(ct[c],group_name=gnames.get(ct[c]['group']),source='src/main/data_800E8300.c:%d'%ct[c]['line']),
      stats=s,bars=bars,stats_source='disc ZZZZ.dat+0x06CF8800 record %d at file offset 0x%X'%(c,c*0xA0)))
presets=[]
capid=[0,4,10,2,6,9,1,5,11,3,17,19]
for n in range(12):
    p=d[0x4380+n*0x48:0x4380+n*0x48+0x48]
    presets.append(dict(index=n,captain_char=capid[n],captain=pretty[names[capid[n]]],rows=[[x for x in p[k*0x12:k*0x12+9]] for k in range(4)],rows_extra=[list(p[k*0x12+9:k*0x12+18]) for k in range(4)]))
teams=[]
for ci,cap in enumerate(caps):
    pre=presets[ci]['rows'][0]
    members=[x for x in pre]
    derived=[c for c in range(54) if vals[c*28]==ci]
    assert sorted(members)==sorted(derived),(cap,members,derived)
    start=[c for c in derived if vals[c*28+1]<=3]
    assert sorted(start)==sorted(x for x in presets[ci]['rows'][1] if x!=255)
    teams.append(dict(captain=cap,captain_char=capid[ci],members_in_preset_order=[dict(id=m,name=pretty[names[m]],classification=cls[vals[m*28+1]]) for m in members],
      recruited_flag_set_at_start=[pretty[names[m]] for m in start]))
out=dict(sources=dict(
  char_ids='include/mssbTypes.h:78-137',
  challenge_table='src/main/file_80069BDC.c:%d lbl_801094E4 (54 x 0x1C records + 1 trailing 0x1C pad record); loaded by fn_2_46ADC/fn_2_468DC src/menus/auto_00_0003C03C_text.c:1867-1888,1997-2005'%(st+1),
  enums='include/game/UnknownHomes_Game.h:1453-1468 (CHALLENGE_CAPTAIN, CHARACTER_VARIANT_CLASSIFICATION), 1477-1481 (recruitment), 1508-1520 (ChallengeTrackingStruct)',
  stats_file='disc ZZZZ.dat offset 0x06CF8800 size 0x46E0 (DiskFileEntry src/menus/rep_0010.c:59, src/game/rep_0.c:11); layout include/game/character_stats.h:9-39, include/main/charsel_state_type.h:15-17',
  presets='same stats file at +0x4380: presets[12][0x48] (include/main/charsel_state_type.h:17); preset index -> captain via lbl_80108EC4 src/main/file_800639BC.c:1637',
  chartable='src/main/data_800E8300.c:%d lbl_800E8558; struct include/main/menu_globals.h:212-218'%(ct0+1),
  variant_groups='src/main/file_800639BC.c:1639-1650 lbl_80108EDC.groups'),
  characters=chars,teams=teams,presets=presets)
json.dump(out,open(H+'/career_data.json','w'),indent=1)
# markdown
M=[]
A=M.append
A('# Mario Superstar Baseball - Career data reference\n')
A('All facts from the decomp at `decomp/` (paths relative to it) or from the USA disc image. Generated by `~/sp/build_career.py`.\n')
A('## 1. Character IDs (`include/mssbTypes.h:78-137`, enum `CHAR_ID`)\n')
A('| ID | Enum | Name |\n|---|---|---|')
for c in chars: A('| %d | %s | %s |'%(c['id'],c['enum'],c['name']))
A('\n## 2. Captains and sub-captains\n')
A('Captain/sub-captain is defined by `variantClassification` in `lbl_801094E4` (`src/main/file_80069BDC.c:%d`): 0=PRIMARY_CAPTAIN, 1=SECONDARY_CAPTAIN.\n'%(st+1))
A('| Team (CHALLENGE_CAPTAIN) | Captain | Sub-captain |\n|---|---|---|')
for ci,cap in enumerate(caps):
    p=[c['name'] for c in chars if c['challenge']['captain']==cap and c['challenge']['variantClassification']=='PRIMARY_CAPTAIN']
    s=[c['name'] for c in chars if c['challenge']['captain']==cap and c['challenge']['variantClassification']=='SECONDARY_CAPTAIN']
    A('| %d %s | %s | %s |'%(ci,cap,', '.join(p),', '.join(s)))
A('\n`lbl_800E854C[12] = {0,1,4,5,10,11,6,17,2,3,9,19}` (`src/main/data_800E8300.c:87`) is not itself a captain/sub-captain table in code: it is only used as the pool of 12 captain-capable characters for random CPU picks in minigames (`src/game/auto_00_00106DFC_text.c:2270-2273` copies it into `pool[]` and shuffles; `:3536-3554` picks a random unused entry for CPU slots). It happens to list the 6 pairs (primary then secondary) in the order Mario, Peach, Wario, Yoshi, DK, Bowser. The same 12 characters have `StatTable.Captain=1` (stat offset 0x33) and `CharTableEntry._4=1` (all others 0).')
A('Related tables: `lbl_803CB8F0[8] = {0,4,10,2,6,9,0,0}` (`src/main/file_80069BDC.c:2284`) maps CHALLENGE_CAPTAIN -> captain char id; `lbl_80108EC4[12] = {0,4,10,2,6,9,1,5,11,3,17,19}` (`src/main/file_800639BC.c:1637`) maps preset-team index -> captain char id (6 primaries, then Luigi, Daisy, Waluigi, Diddy, Birdo, Bowser Jr.).\n')
A('## 3. Challenge Mode default teams\n')
A('Two independent sources agree (asserted in the script):\n')
A('* Per-character `challengeCaptain` (byte 0) and `variantClassification` (byte 1) come from `lbl_801094E4` (`src/main/file_80069BDC.c:%d`, 0x1C bytes per character; the record is the `ScoutFlagTable` that `ChallengeTrackingStruct.scoutFlagPointer` points to). They are copied into the tracker by `fn_2_46ADC` (`src/menus/auto_00_0003C03C_text.c:1867-1888`, new game) and `fn_2_468DC` (`:1997-2005`). Bytes 2-3 are unknown; bytes 4..27 are a [4][6] scout/limit table indexed `[_4415*6 + _441C + 4]` (`include/menus/menu_work.h:146`).'%(st+1))
A('* New game: `chars[i]._31` (CHALLENGE_RECRUITMENT_CD) = RECRUITED(1) iff `challengeCaptain == chosen captain && variantClassification <= 3` (`src/menus/auto_00_0003C03C_text.c:1882-1886`). So the secondary color variants are not flagged themselves; they become usable through their primary variant (`fn_80067AC8` alt lookup, `src/menus/auto_00_00001254_text.c:3801-3812`).')
A('* The full 9-man team lineup is preset row 0 of `presets[captainIdx]` in the stats file on disc (ZZZZ.dat+0x06CF8800, +0x4380, 0x48 bytes per preset; `include/main/charsel_state_type.h:17`). It is copied into the team slots/ `gChallengeState.teams[]` when starting a challenge (`src/main/file_800639BC.c:1388-1408`, `src/menus/rep_0438.c:121-125`), and used for the CPU opponent team (`src/menus/auto_00_00001254_text.c:1514-1520`). Preset row 1 lists exactly the characters with the recruited flag at start.\n')
for t in teams:
    A('### %s team\n'%pretty[t['captain']])
    A('| Slot | ID | Character | Classification |\n|---|---|---|---|')
    for k,m in enumerate(t['members_in_preset_order']): A('| %d | %d | %s | %s |'%(k+1,m['id'],m['name'],m['classification']))
    A('\nRecruited flag set at new game (class <= 3): %s\n'%', '.join(t['recruited_flag_set_at_start']))
A('Preset 11 (Bowser Jr., `lbl_80108EC4[11]=19`) row 0 is `{48,49,51,19,50,48,49,51,50}` (Dry Bones Gray/Green/Blue, Bowser Jr., Red, then the four repeated) - the final-boss team used for team 1 in `src/main/file_800639BC.c:1399,1422`. Presets 6-10 (Luigi, Daisy, Waluigi, Diddy, Birdo) have row 0 all 0xFF. Rows 1-3 of every preset are partial 5-man teams (row 3 = captain alone) chosen by `src/menus/auto_00_00001254_text.c:2741-2757`.\n')
A('### Full per-character challenge classification\n')
A('| ID | Character | challengeCaptain | variantClassification | Source line |\n|---|---|---|---|---|')
for c in chars: A('| %d | %s | %s | %s | file_80069BDC.c:%s |'%(c['id'],c['name'],c['challenge']['captain'],c['challenge']['variantClassification'],c['challenge']['source'].split(':')[1].split(' ')[0]))
A('\n## 4. Character stats\n')
A('Source: the 0x46E0-byte character file on disc, `ZZZZ.dat` offset 0x06CF8800 (uncompressed DiskFileEntry `{0, 0x46E0, 0x06CF8800, 0x46E0}` at `src/menus/rep_0010.c:59` and `src/game/rep_0.c:11`). It is loaded to `lbl_8034E9A0` (CharSelectState, `roster[6][9]` indexed `[id/9][id%9]`, `include/main/charsel_state_type.h:15`) and per-team copies are made into `inMemRoster` (`src/game/rep_0.c:147-148`). Record = `CharacterStats` 0xA0 bytes (`include/game/character_stats.h:102-115`); first 0x3B bytes = `StatTable` (`:9-39`), then chemistry[54] at 0x3B. Bytes 0x05-0x1F are zero for all 54. The character-select screen draws the 4 bars from `BattingStatBar`/`PitchingStatBar`/`RunningStatBar`/`FieldingStatBar` (`src/menus/auto_00_00071EC4_text.c:4133-4137`).\n')
A('Field offsets: 0x00 CurveBallSpeed, 0x01 FastBallSpeed, 0x02 cursedBall, 0x03 Curve, 0x04 curveControl, 0x20 FieldingStats (u32 FIELDING_ABILITIES bits, `include/game/UnknownHomes_Game.h:1483-1500`), 0x24 CharID, 0x26 FieldingArm, 0x27 BattingStance (BATTING_HAND 0=right,1=left, `mssbTypes.h:139-142`), 0x28 SlapContactSize, 0x29 ChargeContactSize, 0x2A SlapHitPower, 0x2B ChargeHitPower, 0x2C BuntingContactSize, 0x2D HitTrajectoryPushPull, 0x2E HitTrajectoryHighLow, 0x2F Speed, 0x30 ThrowingArm, 0x31 CharacterClass, 0x32 Weight, 0x33 Captain, 0x34 CaptainStarHitPitch, 0x35 NonCaptainStarSwing, 0x36 NonCaptainStarPitch, 0x37 BattingStatBar, 0x38 PitchingStatBar, 0x39 RunningStatBar (=Speed bar), 0x3A FieldingStatBar.\n')
A('### Visible bars\n')
A('| ID | Character | Bat | Pitch | Field | Speed | Total | Class |\n|---|---|---|---|---|---|---|---|')
for c in chars:
    b=c['bars']; A('| %d | %s | %d | %d | %d | %d | %d | %s |'%(c['id'],c['name'],b['Batting'],b['Pitching'],b['Fielding'],b['Speed'],b['Total'],c['stats']['CharacterClass']))
A('\n### Underlying values\n')
A('| ID | Character | Arm | Bat | SlapCt | ChgCt | SlapPw | ChgPw | Bunt | PushPull | HighLow | Speed | Throw | Wt | CurveSpd | FastSpd | Cursed | Curve | CurveCtl | Capt | CaptStar | NCSwing | NCPitch | Fielding abilities |')
A('|'+'---|'*24)
for c in chars:
    s=c['stats']
    A('| %d | %s | %s | %s | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %d | %s |'%(c['id'],c['name'],'L' if s['FieldingArm'] else 'R','L' if s['BattingStance'] else 'R',s['SlapContactSize'],s['ChargeContactSize'],s['SlapHitPower'],s['ChargeHitPower'],s['BuntingContactSize'],s['HitTrajectoryPushPull'],s['HitTrajectoryHighLow'],s['Speed'],s['ThrowingArm'],s['Weight'],s['CurveBallSpeed'],s['FastBallSpeed'],s['cursedBall'],s['Curve'],s['curveControl'],s['Captain'],s['CaptainStarHitPitch'],s['NonCaptainStarSwing'],s['NonCaptainStarPitch'],', '.join(s['FieldingAbilities'])))
A('\n### Generic / variant character bar totals\n')
A('| Family | Member (ID) | Bat/Pitch/Field/Speed | Total |\n|---|---|---|---|')
fam=[('Toad',[13,29,30,31,32]),('Shy Guy',[16,44,45,46,47]),('Koopa Troopa',[12,42]),('Paratroopa',[20,43]),('Magikoopa',[33,34,35,36]),('Dry Bones',[48,49,50,51]),('Bros',[27,52,53]),('Pianta',[21,22,23]),('Noki',[24,25,26]),('Goomba',[40]),('Paragoomba',[41])]
for fn,ids in fam:
    for i in ids:
        b=chars[i]['bars']; A('| %s | %s (%d) | %d/%d/%d/%d | %d |'%(fn,chars[i]['name'],i,b['Batting'],b['Pitching'],b['Fielding'],b['Speed'],b['Total']))
A('\n## 5. Color variants (`lbl_800E8558`, `src/main/data_800E8300.c:%d`)\n'%(ct0+1))
A('Entry layout `{group, baseId, {modelRow, isBase}, captainFlag, variantIndex}` (struct `include/main/menu_globals.h:212-218` names only `_0`, `id`, `_2[2]`, `_4`, `_5`). Nonzero `group` = variant family; same groups as `lbl_80108EDC.groups` (`src/main/file_800639BC.c:1639-1650`, looked up by `fn_80067AC8` at `:1008`).\n')
A('| Group | Family | Members (variantIndex: name) |\n|---|---|---|')
for g in range(1,10):
    mem=[c for c in chars if c['charTable']['group']==g]
    mem.sort(key=lambda c:c['charTable']['variant_index'])
    A('| %d | %s | %s |'%(g,gnames[g],'; '.join('%d: %s (id %d, line %d)'%(c['charTable']['variant_index'],c['name'],c['id'],c['charTable']['line']) for c in mem)))
A('\nAll other characters (group 0) have no color variants, including Goomba and Paragoomba.\n')
open(H+'/career_data.md','w').write('\n'.join(M))
print('ok')
