/* menu_data.h: menu structure for Fuse
   Copyright (c) 2004 Marek Januszewski

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
#define IDM_MENU_FILE_SAVE_SNAPSHOT 102
#define IDM_MENU_FILE_RECORDING 103
#define IDM_MENU_FILE_RECORDING_RECORD 104
#define IDM_MENU_FILE_RECORDING_RECORD_FROM_SNAPSHOT 105
#define IDM_MENU_FILE_RECORDING_PLAY 106
#define IDM_MENU_FILE_RECORDING_STOP 107
#define IDM_MENU_FILE_AY_LOGGING 108
#define IDM_MENU_FILE_AY_LOGGING_RECORD 109
#define IDM_MENU_FILE_AY_LOGGING_STOP 110

#define IDM_MENU_FILE_OPEN_SCR_SCREENSHOT 111
#define IDM_MENU_FILE_SAVE_SCREEN_AS_SCR 112
#define IDM_MENU_FILE_SAVE_SCREEN_AS_PNG 113

#define IDM_MENU_FILE_LOAD_BINARY_DATA 114
#define IDM_MENU_FILE_SAVE_BINARY_DATA 115

#define IDM_MENU_FILE_EXIT 116
#define IDM_MENU_OPTIONS 117
#define IDM_MENU_OPTIONS_GENERAL 118
#define IDM_MENU_OPTIONS_SOUND 119
#define IDM_MENU_OPTIONS_PERIPHERIALS 120
#define IDM_MENU_OPTIONS_RZX 121
#define IDM_MENU_OPTIONS_JOYSTICKS 122
#define IDM_MENU_OPTIONS_JOYSTICKS_JOYSTICK_1 123
#define IDM_MENU_OPTIONS_JOYSTICKS_JOYSTICK_2 124
#define IDM_MENU_OPTIONS_JOYSTICKS_KEYBOARD 125
#define IDM_MENU_OPTIONS_SELECT_ROMS 126
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_16K 127
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_48K 128
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_128K 129
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_2 130
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_2A 131
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_3 132
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_3E 133
#define IDM_MENU_OPTIONS_SELECT_ROMS_TIMEX_TC2048 134
#define IDM_MENU_OPTIONS_SELECT_ROMS_TIMEX_TC2068 135
#define IDM_MENU_OPTIONS_SELECT_ROMS_PENTAGON_128K 136
#define IDM_MENU_OPTIONS_SELECT_ROMS_SCORPION_ZS_256 137
#define IDM_MENU_OPTIONS_SELECT_ROMS_SPECTRUM_SE 138
#define IDM_MENU_OPTIONS_FILTER 139

#define IDM_MENU_OPTIONS_SAVE 140
#define IDM_MENU_MACHINE 141
#define IDM_MENU_MACHINE_PAUSE 142
#define IDM_MENU_MACHINE_RESET 143
#define IDM_MENU_MACHINE_SELECT 144
#define IDM_MENU_MACHINE_DEBUGGER 145
#define IDM_MENU_MACHINE_POKE_FINDER 146
#define IDM_MENU_MACHINE_MEMORY_BROWSER 147
#define IDM_MENU_MACHINE_NMI 148
#define IDM_MENU_MEDIA 149
#define IDM_MENU_MEDIA_TAPE 150
#define IDM_MENU_MEDIA_TAPE_OPEN 151
#define IDM_MENU_MEDIA_TAPE_PLAY 152
#define IDM_MENU_MEDIA_TAPE_BROWSE 153
#define IDM_MENU_MEDIA_TAPE_REWIND 154
#define IDM_MENU_MEDIA_TAPE_CLEAR 155
#define IDM_MENU_MEDIA_TAPE_WRITE 156
#define IDM_MENU_MEDIA_DISK 157
#define IDM_MENU_MEDIA_DISK_DRIVE_A 158
#define IDM_MENU_MEDIA_DISK_DRIVE_A_INSERT 159
#define IDM_MENU_MEDIA_DISK_DRIVE_A_EJECT 160
#define IDM_MENU_MEDIA_DISK_DRIVE_A_EJECT_AND_WRITE 161
#define IDM_MENU_MEDIA_DISK_DRIVE_B 162
#define IDM_MENU_MEDIA_DISK_DRIVE_B_INSERT 163
#define IDM_MENU_MEDIA_DISK_DRIVE_B_EJECT 164
#define IDM_MENU_MEDIA_DISK_DRIVE_B_EJECT_AND_WRITE 165
#define IDM_MENU_MEDIA_CARTRIDGE 166
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEX_DOCK 167
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEX_DOCK_INSERT 168
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEX_DOCK_EJECT 169
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACE_II 170
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACE_II_INSERT 171
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACE_II_EJECT 172
#define IDM_MENU_MEDIA_IDE 173
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT 174
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_MASTER 175
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_MASTER_INSERT 176
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_MASTER_COMMIT 177
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_MASTER_EJECT 178
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_SLAVE 179
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_SLAVE_INSERT 180
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_SLAVE_COMMIT 181
#define IDM_MENU_MEDIA_IDE_SIMPLE_8_BIT_SLAVE_EJECT 182
#define IDM_MENU_MEDIA_IDE_ZXATASP 183
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER 184
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_INSERT 185
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_COMMIT 186
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_EJECT 187
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE 188
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_INSERT 189
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_COMMIT 190
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_EJECT 191
#define IDM_MENU_MEDIA_IDE_ZXCF_COMPACTFLASH 192
#define IDM_MENU_MEDIA_IDE_ZXCF_COMPACTFLASH_INSERT 193
#define IDM_MENU_MEDIA_IDE_ZXCF_COMPACTFLASH_COMMIT 194
#define IDM_MENU_MEDIA_IDE_ZXCF_COMPACTFLASH_EJECT 195
#define IDM_MENU_HELP 196
#define IDM_MENU_HELP_KEYBOARD 197

void handle_menu( DWORD cmd, HWND okno );

