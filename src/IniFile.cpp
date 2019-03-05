/* IniFile.cpp
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
#include <fstream>
#include <string>
#include "IniFile.h"
#include "ConfigItem.h"


// Update
int IniFile::update()
{
    ConfigItem * aux = nullptr;
    std::string line;
    std::size_t token_position;

    while (fileStream >> line) {
        if (line.front() == SECTION_START && line.back() == SECTION_END)
        {
            if (teste == nullptr)
            {
                teste = new ConfigItem();
                teste->setName(line.substr(1, line.length()-2));
            }
            else
            {
                aux = teste;
                while (aux->getNext() != nullptr)
                {
                    aux = aux->getNext();
                }
                ConfigItem * newConfigItem = new ConfigItem();
                newConfigItem->setName(line.substr(1, line.length()-2));
                aux->setNext(newConfigItem);
            }

            continue;
        }
        token_position = line.find(VARIABLE_TOKEN);
        if (token_position!=std::string::npos)
        {
            std::cout << '\t' << line.substr(0, token_position);
            std::cout << '\t' << line.substr(token_position+1, line.length()) << std::endl;
        }
    }
    aux = teste;
    do
    {
        std::cout << aux->getName() << std::endl;
        aux = aux->getNext();
    } while (aux->getNext() != nullptr);
    std::cout << aux->getName() << std::endl;

    return 0;
}

// Open a file called <file_name>
int IniFile::openFile(char * fileName)
{
    fileStream.open(fileName, std::ios::in | std::ios::out);

    if (!fileStream.is_open())
    {
        std::cerr << "ERROR: File "
                  << fileName
                  << " could not be opened"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    return update();
}

//
int IniFile::readInteger(char * sectionName, char * name, int defaultValue)
{
    return 0;
}

//
char * IniFile::readString(char * sectionName, char * name, char * defaultValue)
{
    return 0;
}

//
bool IniFile::readBoolean(char * sectionName, char * name, bool defaultValue)
{
    return 0;
}

//
int IniFile::writeInteger(char * sectionName, char * name, int value)
{
    return 0;
}

//
int IniFile::writeString(char * sectionName, char * name, char * value)
{
    return 0;
}

//
int IniFile::writeBolean(char * sectionName, char * name, bool value)
{
    return 0;
}

// close the file
int IniFile::closeFile()
{
    fileStream.close();

    return 0;
}

