/* ConfigItem.h
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

#ifndef CONFIG_ITEM_H
#define CONFIG_ITEM_H


class ConfigItem
{
private:
    std::string name;
    std::string value;
    ConfigItem * nextConfigItem = nullptr;
public:
    ConfigItem() = default;

    int setName(const std::string & name);
    std::string getName();
    int setValue(const std::string & value);
    std::string getValue();
    int setNext(ConfigItem * item);
    ConfigItem * getNext();
};

#endif
