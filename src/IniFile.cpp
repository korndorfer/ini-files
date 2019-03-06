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
#include <cstring>
#include <cctype>
#include <iomanip>
#include "IniFile.h"
#include "Ini.h"


IniSection * IniFile::setSection(std::string name)
{
    IniSection * newSection = new IniSection(name);

    if (sections == nullptr)
    {
        sections = newSection;
        return sections;
    }
    else if (sections->isName(name))
    {
        std::cout << "ERROR: The name "
                  << name
                  << " was already in list!"
                  << std::endl;
    }
    else
    {
        IniSection * auxSection = sections;
        while (auxSection->getNext() != nullptr)
        {
            if (auxSection->isName(name))
            {
                std::cout << "ERROR: The name "
                          << name
                          << " was already in list!"
                          << std::endl;
            }
            auxSection = (IniSection *) auxSection->getNext();
        }
        auxSection->setNext(newSection);
    }

    return newSection;
}

IniSection * IniFile::getSection(std::string name)
{
    IniSection * auxSection = sections;
    if (sections != nullptr && !sections->isName(name))
    {
        while (auxSection->getNext() != nullptr)
        {
            if (auxSection->isName(name))
            {
                break;
            }
            else
            {
                auxSection = (IniSection *) auxSection->getNext();
            }
        }
    }

    return auxSection;
}

// Update
int IniFile::update()
{
    IniSection * section = nullptr;
    std::string line;
    std::size_t start_position = 0;
    std::size_t final_position = 0;
    std::size_t token_position = 0;

    while (std::getline(fileStream, line)) {
        start_position = line.find(SECTION_START);
        final_position = line.find(SECTION_END);
        if (start_position != std::string::npos &&
            final_position != std::string::npos)
        {
            final_position = final_position - start_position - 1;
            start_position = start_position + 1;
            section = setSection(line.substr(start_position, final_position));
        }
        else
        {
            token_position = line.find(VARIABLE_TOKEN);
            if (token_position != std::string::npos)
            {
                if (section != nullptr)
                {
                    section->setItem(line.substr(0, token_position),
                                     line.substr(token_position+1,
                                                 line.length()));
                }
                else
                {
                    std::cout << "ERROR: Item "
                              << line
                              << " without section!"
                              << std::endl;
                }
            }
        }
    }

    return 0;
}

void IniFile::listSections()
{
    IniSection * aux = nullptr;
    IniItem * auxItem = nullptr;

    if (sections != nullptr)
    {
        aux = sections;
        while (aux->getNext() != nullptr)
        {
            std::cout << aux->getName() << std::endl;
            if (aux->getItems() != nullptr)
            {
                auxItem = aux->getItems();
                while (auxItem->getNext() != nullptr)
                {
                    std::cout << '\t'
                              << std::setw(21)
                              << std::left
                              << auxItem->getName()
                              << auxItem->getValue() << std::endl;

                    auxItem = (IniItem *) auxItem->getNext();
                }
                std::cout << '\t'
                          << std::setw(21)
                          << std::left
                          << auxItem->getName()
                          << auxItem->getValue() << std::endl;
            }

            aux = (IniSection *) aux->getNext();
        }

        std::cout << aux->getName() << std::endl;
        if (aux->getItems() != nullptr)
        {
            auxItem = aux->getItems();
            while (auxItem->getNext() != nullptr)
            {
                std::cout << '\t'
                          << std::setw(21)
                          << std::left
                          << auxItem->getName()
                          << auxItem->getValue() << std::endl;

                auxItem = (IniItem *) auxItem->getNext();
            }
            std::cout << '\t'
                      << std::setw(21)
                      << std::left
                      << auxItem->getName()
                      << auxItem->getValue() << std::endl;
        }
    }
}

// Open a file called <fileName>
int IniFile::openFile(char * fileName)
{
    fileStream.open(fileName);

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
    IniSection * section = getSection(sectionName);
    IniItem * item = section->getItem(name);

    if (item != nullptr)
    {
        return std::stoi(item->getValue());
    }
    else
    {
        return defaultValue;
    }
}

//
char * IniFile::readString(char * sectionName, char * name, char * defaultValue)
{
    IniSection * section = getSection(sectionName);
    IniItem * item = section->getItem(name);

    if (item != nullptr)
    {
        std::string value = item->getValue();
        char * result = new char[value.length()+1];
        std::strcpy(result, value.c_str());
        return result;
    }
    else
    {
        return defaultValue;
    }
}

//
bool IniFile::readBoolean(char * sectionName, char * name, bool defaultValue)
{
    IniSection * section = getSection(sectionName);
    IniItem * item = section->getItem(name);

    if (item != nullptr)
    {
        int index = 0;
        std::string value = item->getValue();
        std::string result = value;
        for (index = 0; index < value.length(); index ++)
        {
            result[index] = std::tolower(value[index]);
        }
        if (result == "true" || result == "1")
        {
            return true;
        }
        else if (result == "false" || result == "0")
        {
            return false;
        }
    }

    return defaultValue;
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

