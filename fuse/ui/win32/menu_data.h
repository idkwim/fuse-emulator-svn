/* menu_data.h: menu structure for Fuse
   Copyright (c) 2004-2007 Philip Kendall, Stuart Brady, Marek Januszewski

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#include <windows.h>

#define IDM_MENU_FILE 100
#define IDM_MENU_FILE_OPEN 101
#define IDM_MENU_FILE_SAVESNAPSHOT 102
#define IDM_MENU_FILE_RECORDING 103
#define IDM_MENU_FILE_RECORDING_RECORD 104
#define IDM_MENU_FILE_RECORDING_RECORDFROMSNAPSHOT 105
#define IDM_MENU_FILE_RECORDING_INSERTSNAPSHOT 106
#define IDM_MENU_FILE_RECORDING_ROLLBACK 107
#define IDM_MENU_FILE_RECORDING_ROLLBACKTO 108
#define IDM_MENU_FILE_RECORDING_PLAY 109
#define IDM_MENU_FILE_RECORDING_STOP 110
#define IDM_MENU_FILE_AYLOGGING 111
#define IDM_MENU_FILE_AYLOGGING_RECORD 112
#define IDM_MENU_FILE_AYLOGGING_STOP 113
#define IDM_MENU_FILE_OPENSCRSCREENSHOT 114
#define IDM_MENU_FILE_SAVESCREENASSCR 115
#define IDM_MENU_FILE_SAVESCREENASPNG 116
#define IDM_MENU_FILE_MOVIES 117
#define IDM_MENU_FILE_MOVIES_RECORDMOVIEASSCR 118
#define IDM_MENU_FILE_MOVIES_RECORDMOVIEASPNG 119
#define IDM_MENU_FILE_MOVIES_STOPMOVIERECORDING 120
#define IDM_MENU_FILE_LOADBINARYDATA 121
#define IDM_MENU_FILE_SAVEBINARYDATA 122
#define IDM_MENU_FILE_EXIT 123
#define IDM_MENU_OPTIONS 124
#define IDM_MENU_OPTIONS_GENERAL 125
#define IDM_MENU_OPTIONS_SOUND 126
#define IDM_MENU_OPTIONS_PERIPHERALS 127
#define IDM_MENU_OPTIONS_RZX 128
#define IDM_MENU_OPTIONS_JOYSTICKS 129
#define IDM_MENU_OPTIONS_JOYSTICKS_JOYSTICK1 130
#define IDM_MENU_OPTIONS_JOYSTICKS_JOYSTICK2 131
#define IDM_MENU_OPTIONS_JOYSTICKS_KEYBOARD 132
#define IDM_MENU_OPTIONS_SELECTROMS 133
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM16K 134
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM48K 135
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM128K 136
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM2 137
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM2A 138
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM3 139
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM3E 140
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTC2048 141
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTC2068 142
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTS2068 143
#define IDM_MENU_OPTIONS_SELECTROMS_PENTAGON128K 144
#define IDM_MENU_OPTIONS_SELECTROMS_SCORPIONZS256 145
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUMSE 146
#define IDM_MENU_OPTIONS_SELECTROMS_INTERFACEI 147
#define IDM_MENU_OPTIONS_FILTER 148
#define IDM_MENU_MACHINE 149
#define IDM_MENU_MACHINE_PAUSE 150
#define IDM_MENU_MACHINE_RESET 151
#define IDM_MENU_MACHINE_SELECT 152
#define IDM_MENU_MACHINE_DEBUGGER 153
#define IDM_MENU_MACHINE_POKEFINDER 154
#define IDM_MENU_MACHINE_MEMORYBROWSER 155
#define IDM_MENU_MACHINE_PROFILER 156
#define IDM_MENU_MACHINE_PROFILER_START 157
#define IDM_MENU_MACHINE_PROFILER_STOP 158
#define IDM_MENU_MACHINE_NMI 159
#define IDM_MENU_MEDIA 160
#define IDM_MENU_MEDIA_TAPE 161
#define IDM_MENU_MEDIA_TAPE_OPEN 162
#define IDM_MENU_MEDIA_TAPE_PLAY 163
#define IDM_MENU_MEDIA_TAPE_BROWSE 164
#define IDM_MENU_MEDIA_TAPE_REWIND 165
#define IDM_MENU_MEDIA_TAPE_CLEAR 166
#define IDM_MENU_MEDIA_TAPE_WRITE 167
#define IDM_MENU_MEDIA_INTERFACEI 168
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1 169
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_INSERTNEW 170
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_INSERT 171
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_SYNC 172
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_EJECT 173
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT 174
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT_SET 175
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT_REMOVE 176
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2 177
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_INSERTNEW 178
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_INSERT 179
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_SYNC 180
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_EJECT 181
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT 182
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT_SET 183
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT_REMOVE 184
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3 185
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_INSERTNEW 186
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_INSERT 187
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_SYNC 188
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_EJECT 189
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT 190
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT_SET 191
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT_REMOVE 192
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4 193
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_INSERTNEW 194
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_INSERT 195
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_SYNC 196
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_EJECT 197
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT 198
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT_SET 199
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT_REMOVE 200
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5 201
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_INSERTNEW 202
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_INSERT 203
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_SYNC 204
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_EJECT 205
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT 206
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT_SET 207
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT_REMOVE 208
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6 209
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_INSERTNEW 210
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_INSERT 211
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_SYNC 212
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_EJECT 213
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT 214
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT_SET 215
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT_REMOVE 216
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7 217
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_INSERTNEW 218
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_INSERT 219
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_SYNC 220
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_EJECT 221
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT 222
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT_SET 223
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT_REMOVE 224
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8 225
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_INSERTNEW 226
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_INSERT 227
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_SYNC 228
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_EJECT 229
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT 230
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT_SET 231
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT_REMOVE 232
#define IDM_MENU_MEDIA_INTERFACEI_RS232 233
#define IDM_MENU_MEDIA_INTERFACEI_RS232_PLUGRXD 234
#define IDM_MENU_MEDIA_INTERFACEI_RS232_UNPLUGRXD 235
#define IDM_MENU_MEDIA_INTERFACEI_RS232_PLUGTXD 236
#define IDM_MENU_MEDIA_INTERFACEI_RS232_UNPLUGTXD 237
#define IDM_MENU_MEDIA_INTERFACEI_SINCLAIRNET 238
#define IDM_MENU_MEDIA_INTERFACEI_SINCLAIRNET_PLUGIN 239
#define IDM_MENU_MEDIA_INTERFACEI_SINCLAIRNET_UNPLUG 240
#define IDM_MENU_MEDIA_DISK 241
#define IDM_MENU_MEDIA_DISK_3 242
#define IDM_MENU_MEDIA_DISK_3_DRIVEA 243
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_INSERT 244
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_EJECT 245
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_EJECTANDWRITE 246
#define IDM_MENU_MEDIA_DISK_3_DRIVEB 247
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_INSERT 248
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_EJECT 249
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_EJECTANDWRITE 250
#define IDM_MENU_MEDIA_DISK_TRDOS 251
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEA 252
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEA_INSERT 253
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEA_EJECT 254
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEA_EJECTANDWRITE 255
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEB 256
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEB_INSERT 257
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEB_EJECT 258
#define IDM_MENU_MEDIA_DISK_TRDOS_DRIVEB_EJECTANDWRITE 259
#define IDM_MENU_MEDIA_CARTRIDGE 260
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK 261
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_INSERT 262
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_EJECT 263
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII 264
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII_INSERT 265
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII_EJECT 266
#define IDM_MENU_MEDIA_IDE 267
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT 268
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER 269
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_INSERT 270
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_COMMIT 271
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_EJECT 272
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE 273
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_INSERT 274
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_COMMIT 275
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_EJECT 276
#define IDM_MENU_MEDIA_IDE_ZXATASP 277
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER 278
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_INSERT 279
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_COMMIT 280
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_EJECT 281
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE 282
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_INSERT 283
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_COMMIT 284
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_EJECT 285
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH 286
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_INSERT 287
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_COMMIT 288
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_EJECT 289
#define IDM_MENU_MEDIA_IDE_DIVIDE 290
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER 291
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_INSERT 292
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_COMMIT 293
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_EJECT 294
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE 295
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_INSERT 296
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_COMMIT 297
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_EJECT 298
#define IDM_MENU_HELP 299
#define IDM_MENU_HELP_KEYBOARD 300

void handle_menu( DWORD cmd, HWND okno );