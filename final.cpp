#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum class ItemType { Shield, Knife, Sword };
enum class Race { Human, Dragon, Giant, Elf, Dwarf };

class Item {
public:
    int id;
    ItemType type;
    int power;
    int usage;

    Item(int id, ItemType type, int power, int usage)
        : id(id), type(type), power(power), usage(usage) {}
};

class Character {
public:
    int id;
    std::string name;
    Race race;
    int level;
    int health;
    std::vector<Item> items;

    Character(int id, std::string name, Race race)
        : id(id), name(name), race(race), level(1), health(getHealthByRace(race)) {}

    void addItem(const Item& item) {
        if (items.size() >= getMaxItemsByLevel(level)) {
            std::cout << "Cannot add more items, maximum limit reached for this level.\n";
            return;
        }
        items.push_back(item);
    }

    void editItem(int itemId, int newPower) {
        auto it = std::find_if(items.begin(), items.end(), [itemId](const Item& item) { return item.id == itemId; });
        if (it != items.end()) {
            it->power = newPower;
        } else {
            std::cout << "Item not found.\n";
        }
    }

    void removeItem(int itemId) {
        items.erase(std::remove_if(items.begin(), items.end(), [itemId](const Item& item) { return item.id == itemId; }), items.end());
    }

    static int getHealthByRace(Race race) {
        switch (race) {
            case Race::Human: return 100;
            case Race::Dragon: return 700;
            case Race::Giant: return 500;
            case Race::Elf: return 300;
            case Race::Dwarf: return 200;
            default: return 100;
        }
    }

private:
    static int getMaxItemsByLevel(int level) {
        if (level < 5) return 2;
        if (level < 10) return 4;
        return 8;
    }
};

std::vector<Item> items;
std::vector<Character> characters;

void createItem();
void createCharacter();
void assignItemToCharacter();
void editItem();
void editCharacter();
void battle();
void printMenu();

int main() {
    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: createItem(); break;
            case 2: createCharacter(); break;
            case 3: assignItemToCharacter(); break;
            case 4: editItem(); break;
            case 5: editCharacter(); break;
            case 6: battle(); break;
            case 7: return 0;
            default: std::cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}

void printMenu() {
    std::cout << "1. Create Item\n";
    std::cout << "2. Create Character\n";
    std::cout << "3. Assign Item to Character\n";
    std::cout << "4. Edit Item\n";
    std::cout << "5. Edit Character\n";
    std::cout << "6. Battle\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

void createItem() {
    int id, power, usage;
    int type;
    std::cout << "Enter item ID: ";
    std::cin >> id;
    std::cout << "Enter item type (0: Shield, 1: Knife, 2: Sword): ";
    std::cin >> type;
    std::cout << "Enter item power: ";
    std::cin >> power;
    std::cout << "Enter item usage: ";
    std::cin >> usage;

    items.emplace_back(id, static_cast<ItemType>(type), power, usage);
    std::cout << "Item created successfully.\n";
}

void createCharacter() {
    int id;
    std::string name;
    int race;
    std::cout << "Enter character ID: ";
    std::cin >> id;
    std::cout << "Enter character name: ";
    std::cin >> name;
    std::cout << "Enter character race (0: Human, 1: Dragon, 2: Giant, 3: Elf, 4: Dwarf): ";
    std::cin >> race;

    characters.emplace_back(id, name, static_cast<Race>(race));
    std::cout << "Character created successfully.\n";
}

void assignItemToCharacter() {
    int charId, itemId;
    std::cout << "Enter character ID: ";
    std::cin >> charId;
    std::cout << "Enter item ID: ";
    std::cin >> itemId;

    auto charIt = std::find_if(characters.begin(), characters.end(), [charId](const Character& c) { return c.id == charId; });
    auto itemIt = std::find_if(items.begin(), items.end(), [itemId](const Item& i) { return i.id == itemId; });

    if (charIt != characters.end() && itemIt != items.end()) {
        charIt->addItem(*itemIt);
        std::cout << "Item assigned successfully.\n";
    } else {
        std::cout << "Character or item not found.\n";
    }
}

void editItem() {
    int itemId, newPower;
    std::cout << "Enter item ID to edit: ";
    std::cin >> itemId;
    std::cout << "Enter new power for the item: ";
    std::cin >> newPower;

    auto itemIt = std::find_if(items.begin(), items.end(), [itemId](const Item& i) { return i.id == itemId; });
    if (itemIt != items.end()) {
        itemIt->power = newPower;
        std::cout << "Item edited successfully.\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void editCharacter() {
    int charId;
    std::cout << "Enter character ID to edit: ";
    std::cin >> charId;

    auto charIt = std::find_if(characters.begin(), characters.end(), [charId](const Character& c) { return c.id == charId; });
    if (charIt != characters.end()) {
        std::string newName;
        int newRace;
        std::cout << "Enter new name for the character: ";
        std::cin >> newName;
        std::cout << "Enter new race for the character (0: Human, 1: Dragon, 2: Giant, 3: Elf, 4: Dwarf): ";
        std::cin >> newRace;

        charIt->name = newName;
        charIt->race = static_cast<Race>(newRace);
        charIt->health = Character::getHealthByRace(static_cast<Race>(newRace));
        std::cout << "Character edited successfully.\n";
    } else {
        std::cout << "Character not found.\n";
    }
}

void battle() {
    int charId1, charId2;
    std::cout << "Enter ID of the first character: ";
    std::cin >> charId1;
    std::cout << "Enter ID of the second character: ";
    std::cin >> charId2;

    auto charIt1 = std::find_if(characters.begin(), characters.end(), [charId1](const Character& c) { return c.id == charId1; });
    auto charIt2 = std::find_if(characters.begin(), characters.end(), [charId2](const Character& c) { return c.id == charId2; });

    if (charIt1 == characters.end() || charIt2 == characters.end()) {
        std::cout << "One or both characters not found.\n";
        return;
    }

    Character& char1 = *charIt1;
    Character& char2 = *charIt2;

    while (char1.health > 0 && char2.health > 0) {
        std::cout << "Character 1 (ID: " << char1.id << ") - Health: " << char1.health << "\n";
        std::cout << "Character 2 (ID: " << char2.id << ") - Health: " << char2.health << "\n";

        int choice;
        std::cout << "1. Attack\n";
        std::cout << "2. Use Shield\n";
        std::cout << "3. Surrender\n";
        std::cout << "Enter choice for character 1: ";
        std::cin >> choice;

        if (choice == 1) {
            // Attack logic for character 1
            if (!char1.items.empty()) {
                char2.health -= char1.items[0].power;  // Simplified attack logic
                std::cout << "Character 1 attacks Character 2 for " << char1.items[0].power << " damage.\n";
                char1.items[0].usage--;
                if (char1.items[0].usage <= 0) {
                    char1.items.erase(char1.items.begin());
                }
            } else {
                std::cout << "Character 1 has no items to attack with.\n";
            }
        } else if (choice == 2) {
            // Use shield logic
            std::cout << "Character 1 uses shield, damage will be halved for the next attack.\n";
        } else if (choice == 3) {
            std::cout << "Character 1 surrenders. Character 2 wins.\n";
            char2.level++;
            char2.health = Character::getHealthByRace(char2.race);
            return;
        }

        if (char2.health <= 0) {
            std::cout << "Character 2 is defeated. Character 1 wins.\n";
            char1.level++;
            char1.health = Character::getHealthByRace(char1.race);
            return;
        }

        // Character 2's turn
        std::cout << "1. Attack\n";
        std::cout << "2. Use Shield\n";
        std::cout << "3. Surrender\n";
        std::cout << "Enter choice for character 2: ";
        std::cin >> choice;

        if (choice == 1) {
            // Attack logic for character 2
            if (!char2.items.empty()) {
                char1.health -= char2.items[0].power;  // Simplified attack logic
                std::cout << "Character 2 attacks Character 1 for " << char2.items[0].power << " damage.\n";
                char2.items[0].usage--;
                if (char2.items[0].usage <= 0) {
                    char2.items.erase(char2.items.begin());
                }
            } else {
                std::cout << "Character 2 has no items to attack with.\n";
            }
        } else if (choice == 2) {
            // Use shield logic
            std::cout << "Character 2 uses shield, damage will be halved for the next attack.\n";
        } else if (choice == 3) {
            std::cout << "Character 2 surrenders. Character 1 wins.\n";
            char1.level++;
            char1.health = Character::getHealthByRace(char1.race);
            return;
        }

        if (char1.health <= 0) {
            std::cout << "Character 1 is defeated. Character 2 wins.\n";
            char2.level++;
            char2.health = Character::getHealthByRace(char2.race);
            return;
        }
    }
}
