/* IniConfig.cpp
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
#include <string>
#include "Ini.h"

bool IniNode::isName(const std::string & data)
{
    return name == data;
}

int IniNode::setName(const std::string & data)
{
    name = data;

    return 0;
}

std::string IniNode::getName()
{
    return name;
}

int IniNode::setNext(IniNode * node)
{
    nextNode = node;

    return 0;
}

IniNode * IniNode::getNext()
{
    return nextNode;
}

int IniItem::setValue(const std::string & data)
{
    value = data;

    return 0;
}

std::string IniItem::getValue()
{
    return value;
}

IniItem * IniSection::setItem(std::string name, std::string value)
{
    IniItem * auxItem = items;
    IniItem * newItem = new IniItem(name, value);

    if (items == nullptr)
    {
        items = newItem;
        return items;
    }
    else if (auxItem->isName(name))
    {
        std::cout << "ERROR: The name "
                  << name
                  << " was already in list!"
                  << std::endl;
    }
    else
    {
        while (auxItem->getNext() != nullptr)
        {
            if (auxItem->isName(name))
            {
                std::cout << "ERROR: The name "
                          << name
                          << " was already in list!"
                          << std::endl;
            }
            auxItem = (IniItem *) auxItem->getNext();
        }
        auxItem->setNext(newItem);
    }

    return auxItem;
}

IniItem * IniSection::getItem(std::string name)
{
    IniItem * auxItem = items;
    if (items != nullptr && !items->isName(name))
    {
        while (auxItem->getNext() != nullptr)
        {
            if (auxItem->isName(name))
            {
                break;
            }
            else
            {
                auxItem = (IniItem *) auxItem->getNext();
            }
        }
    }

    return auxItem;
}

IniItem * IniSection::setItems(IniItem * data)
{
    items = data;
    return items;
}

IniItem * IniSection::getItems()
{
    return items;
}


