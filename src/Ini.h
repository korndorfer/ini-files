/* IniConfig.h
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

#include <string>

#ifndef INI_H
#define INI_H


class IniNode
{
private:
    std::string name;
    IniNode * nextNode = nullptr;
public:
    IniNode(std::string & name) : name(name) {};
    IniNode() = default;

    bool isName(const std::string & name);
    int setName(const std::string & name);
    std::string getName();
    int setNext(IniNode * node);
    IniNode * getNext();
};


class IniItem: public IniNode
{
private:
    std::string value;
public:
    IniItem(std::string & name, std::string & data) : IniNode(name)
    {
        value = data;
    };
    IniItem() = default;

    int setValue(const std::string & value);
    std::string getValue();
};

class IniSection: public IniNode
{
private:
    IniItem * items = nullptr;
public:
    IniSection(std::string & name) : IniNode(name) {};

    IniSection() = default;

    IniItem * setItem(std::string name, std::string value);
    IniItem * getItem(std::string name);
    IniItem * setItems(IniItem * data);
    IniItem * getItems();
};

bool hasNode(std::string name, IniNode ** node);

#endif

