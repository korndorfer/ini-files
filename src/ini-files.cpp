/* ini-files.cpp
 *
 * Copyright 2019 Israel Cristiano Korndörfer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <iostream>
#include "IniFile.h"

#define FILE_NAME "data/data.ini"


int main (int argc, char *argv[])
{
    IniFile iniFile;

    iniFile.openFile((char *) FILE_NAME);
    std::cout << iniFile.readString((char *) "FTP", (char *) "SUPassword", (char *) "nothing") << std::endl;
    std::cout << iniFile.readInteger((char *) "FTP", (char *) "FTPDataPort", 23) << std::endl;
    std::cout << iniFile.readBoolean((char *) "BACKUP_SERVERS", (char *) "CustomFTP", false) << std::endl;
    iniFile.closeFile();

    return EXIT_SUCCESS;
}

