#include "knight2.h"

/* * * BEGIN implementation of class BaseItem * * */

///// ANTIDOTE

bool  Antidote::canUse(BaseKnight* knight) {
    if (knight->IsPoisonous())
    {
        return true;
    }
    else {
        return false;
    }
};
void Antidote::use(BaseKnight* knight) {
    if (knight->Get_Bag()->get(ANTIDOTE) != nullptr) {
        knight->Poisonous(false);
    }
}
ItemType Antidote::getType() const {
    return ItemType::ANTIDOTE;
}

///// PHOENIXDOWN_I

bool  PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->Get_HP() == 0) {
        return true;
    }
    else {
        return false;
    }
};
void PhoenixDownI::use(BaseKnight* knight) {
    if (knight->Get_Bag()->get(PHOENIXDOWNI) != nullptr) { knight->Set_HP(knight->Get_MaxHP()); }
}
ItemType PhoenixDownI::getType() const {
    return ItemType::PHOENIXDOWNI;
}

///// PHOENIXDOWN_II

bool  PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->Get_HP() < (knight->Get_MaxHP() / 4)) {
        return true;
    }
    else {
        return false;
    }
};
void PhoenixDownII::use(BaseKnight* knight) {
    if (knight->Get_Bag()->get(PHOENIXDOWNII) != nullptr) { knight->Set_HP(knight->Get_MaxHP()); }
}
ItemType PhoenixDownII::getType() const {
    return ItemType::PHOENIXDOWNII;
}

///// PHOENIXDOWN_III

bool  PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->Get_HP() < (knight->Get_MaxHP() / 3)) {
        return true;
    }
    else {
        return false;
    }
};
void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->Get_Bag()->get(PHOENIXDOWNIII) != nullptr) {
        if (knight->Get_HP() <= 0) {
            knight->Set_HP(knight->Get_MaxHP() / 3);
        }
        else {
            knight->Set_HP(knight->Get_HP() + knight->Get_MaxHP() / 4);
        }
    }
}
ItemType PhoenixDownIII::getType() const {
    return ItemType::PHOENIXDOWNIII;
}

///// PHOENIXDOWN_IV

bool  PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->Get_HP() < (knight->Get_MaxHP() / 2)) {
      //  cout << "sai loai 4" << endl;
        return true;
    }
    else {
        return false;
    }
};
void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->Get_Bag()->get(PHOENIXDOWNIV) != nullptr) {
        if (knight->Get_HP() <= 0) {
        
            knight->Set_HP(knight->Get_MaxHP() / 2);
        }
        else {
            knight->Set_HP((knight->Get_HP() + knight->Get_MaxHP() / 5));
        }
    }
}
ItemType PhoenixDownIV::getType() const {
    return ItemType::PHOENIXDOWNIV;
}

/* * * END implementation of class BaseItem * * */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    max_size = 0;
};

bool BaseBag::insertFirst(BaseItem* item) {
    if (size >= max_size) {
        return false;
    }

    Node* node = new Node(item);
    if (size == 0) {
        head = node;
        tail = node;
    }
    else {
        node->next = head;
        head = node;
    }
    size++;

    return true;
}

BaseItem* BaseBag::get(ItemType itemType) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->item->getType() == itemType) {
            if (previous == nullptr) {
                head = current->next;
                if (head != nullptr) {
                }
                else {
                    tail = nullptr;
                }
            }
            else {
                previous->next = current->next;
                if (current->next != nullptr) {
                }
                else {
                    tail = previous;
                }
            }
            size--;
            BaseItem* item = current->item;
            delete current;
            return item;
        }
        previous = current;
        current = current->next;
    }
    return nullptr;
}

string BaseBag::toString() const {
    stringstream ss;
    ss << "Bag[count=" << size << ";";
    if (size > 0) {
        Node* current = head;
        while (current != nullptr) {
            if (current != head) {
                ss << ",";
            }
            switch (current->item->getType()) {
            case ItemType::ANTIDOTE:
                ss << "Antidote";
                break;
            case ItemType::PHOENIXDOWNI:
                ss << "PhoenixI";
                break;
            case ItemType::PHOENIXDOWNII:
                ss << "PhoenixII";
                break;
            case ItemType::PHOENIXDOWNIII:
                ss << "PhoenixIII";
                break;
            case ItemType::PHOENIXDOWNIV:
                ss << "PhoenixIV";
                break;
            }
            current = current->next;
        }
    }
    ss << "]";
    return ss.str();
}

void BaseBag::drop_items() {
    int drop = 0;
    if (3 > size) {
        drop = size;
    }
    else {
        drop = 3;
    }

    Node* curr = head;
    for (int i = 0; i < drop && curr != nullptr; i++) {
        Node* next = curr->next;
        if (curr->item != nullptr) {
            delete curr->item;
        }
        delete curr;
        curr = next;
        size--;
    }
    head = curr;
    if (curr == nullptr) {
        tail = nullptr;
    }
}

void BaseBag::find_phoenix(BaseKnight* knight_own) {
    if (size > 0) {
        Node* current = head;
        while (current != nullptr) {
            if (current->item->getType() != ANTIDOTE) {
                if (current->item->canUse(knight_own))
                {
                    current->item->use(knight_own);
                    break;
                }
                
            }
            current = current->next;
        }
    }
};

/* * * END implementation of class BaseBag * * */


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

void BaseKnight::Set_HP(int new_HP) {
    if (new_HP > 999) { hp = 999; }
    else if (new_HP < 0)
    {
        hp = 0;
    }
    else {
        hp = new_HP;
    }
};

int BaseKnight::Get_HP() {return hp;};

void BaseKnight::Set_Level(int new_level) {
    if (new_level > 10) {
        level = 10;
    }
    else {
        level = new_level;
    }
};

int BaseKnight::Get_Level() {return level;};

int BaseKnight::Get_MaxHP() {return maxhp;};

void BaseKnight::Set_Gil(int new_gil) {gil = new_gil;};

int BaseKnight::Get_Gil() {return gil;};

BaseBag* BaseKnight::Get_Bag() { return bag; };

KnightType BaseKnight::Get_Knight_Type() {
    return knightType;
};

double BaseKnight::Get_BaseDamage() {
    if (knightType == LANCELOT) {
        return 0.05;
    }
    else if (knightType == PALADIN) {
        return 0.06;
    }
    else {
        return 0.075;
    }
};

bool isPrime(int n) {
    // Check if n is less than 2, since 2 is the smallest prime number
    if (n < 2) {
        return false;
    }
    // Check if n is divisible by any number from 2 to sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    // If n is not divisible by any number from 2 to sqrt(n), then it is a prime number
    return true;
}

bool isPythagoras(int maxhp) {
    if (maxhp < 100 || maxhp > 999) { return false; }
    else {
        int a = maxhp / 100;
        int b = (maxhp / 10) % 10;
        int c = maxhp % 10;
        if ((a * a + b * b == c * c) || (a * a == b * b + c * c) || (a * a + c * c == b * b)) { return true; }
        else {return false; }
    }
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
//    cout << "here" << endl;
    if (isPrime(maxhp))
    {
        PaladinKnight* paladinknight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return paladinknight;
    }
    else if (isPythagoras(maxhp)){
        DragonKnight* dragonknight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return dragonknight;
    }
    else if (maxhp == 888) {
        LancelotKnight* lancelotknight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return lancelotknight;
    }
    else {
        NormalKnight* normalknight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return normalknight;
    }
};

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->level = level;
    this->hp = maxhp;
    this->gil = gil;
    knightType = PALADIN;
    this->bag = new PaladinBag(phoenixdownI,antidote);
};

PaladinKnight::~PaladinKnight() {
    delete bag;
    bag = nullptr;
};

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    knightType = DRAGON;
    this->bag = new DragonBag(phoenixdownI, antidote);
};

DragonKnight::~DragonKnight() {
    delete bag;
    bag = nullptr;
};

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    knightType = LANCELOT;
    this->bag = new LancelotBag(phoenixdownI, antidote);
};

LancelotKnight::~LancelotKnight() {
    delete bag;
    bag = nullptr;
};

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    knightType = NORMAL;
    this->bag = new NormalBag(phoenixdownI, antidote);
};

NormalKnight::~NormalKnight() {
    delete bag;
    bag = nullptr;
};

BaseKnight::BaseKnight() {
    id = 0;
    hp = 0;
    maxhp = 0;
    level = 0;
    gil = 0;
    antidote = 0;
    bag = nullptr;
    knightType = NORMAL;
    poisonous = false;
};

void BaseKnight::Poisonous(bool poison) {poisonous = poison;};

bool BaseKnight::IsPoisonous() {return poisonous;};

/* * * END implementation of class BaseKnight * * */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
};

ArmyKnights::ArmyKnights(const string& file_armyknights) {
    ifstream input_army;
    input_army.open(file_armyknights);
    input_army >> army_count;
    army = new BaseKnight * [army_count];
    int index[5] = { 0,0,0,0,0 };
    for (int i = 0; i < army_count; i++) {
        input_army >> index[0] >> index[1] >> index[2] >> index[3] >> index[4];
        army[i] = BaseKnight::create(i + 1, index[0], index[1], index[3], index[4], index[2]);
    }
    input_army.close();
};

ArmyKnights::~ArmyKnights() {
    delete army;
    army = nullptr;
};

bool ArmyKnights::fight(BaseOpponent* opponent) {
    while (true)
    {
        if (this->lastKnight() != nullptr) {
            int op_id = opponent->get_id();
            int hp_of_last_knight = this->lastKnight()->Get_HP();
            int level_of_last_knight = this->lastKnight()->Get_Level();
            int gil_of_last_knight = this->lastKnight()->Get_Gil();
            if ((this->lastKnight()->Get_Knight_Type() == LANCELOT ||
                this->lastKnight()->Get_Knight_Type() == PALADIN) && (1 <= op_id && op_id <= 5)) {
                gil_of_last_knight += opponent->get_BaseGil();
                Add_Gil(gil_of_last_knight);
                this->Healing();
                return true;
            }
            else {
                if ((level_of_last_knight) >= (opponent->get_levelO())) {
                    gil_of_last_knight += opponent->get_BaseGil();
                    Add_Gil(gil_of_last_knight);
                    this->Healing();
                    return true;
                }
                else {
                    if (opponent->get_id() != 6) {
                        hp_of_last_knight = hp_of_last_knight - (opponent->get_BaseDamage()) * ((opponent->get_levelO()) - level_of_last_knight);
                        this->lastKnight()->Set_HP(hp_of_last_knight);
                        this->Healing();
                        return false;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

        }
        else {
            return false; // khi đoi quan không con hiep si nao , count =0 tra ve lastknight = nullptr
        }
    }
}

void ArmyKnights::Add_Gil(int new_gil) {

    if (new_gil <= 999) {
        this->lastKnight()->Set_Gil(new_gil);
    }
    else {
        int phandu = (new_gil - this->lastKnight()->Get_Gil());
        this->lastKnight()->Set_Gil(999);
        for (int i = army_count - 2; i >= 0; i--)
        {
            if (this->army[i]->Get_Gil() + phandu <= 999) {
                this->army[i]->Set_Gil(phandu + this->army[i]->Get_Gil());
                break;
            }
            else if (i == 0 && (this->army[i]->Get_Gil() + phandu) > 999)
            {
                this->army[0]->Set_Gil(999);
            }
            else {

                phandu = phandu - (999 - this->army[i]->Get_Gil());
                army[i]->Set_Gil(999);
            }

        }
    }
};

void ArmyKnights::Healing() {
    if (this->lastKnight()!=nullptr){
        this->lastKnight()->Get_Bag()->find_phoenix(this->lastKnight());
        if (this->lastKnight()->Get_HP() == 0) {
            if (this->lastKnight()->Get_Gil() >= 100) {
                this->lastKnight()->Set_Gil(this->lastKnight()->Get_Gil() - 100);
                this->lastKnight()->Set_HP(lastKnight()->Get_MaxHP() / 2);
            }
            else { // hồi sinh không thành công
                this->set_army(this->lastKnight());
            }
        }
    }
};

bool ArmyKnights::adventure(Events* events) {

    // i là stt cua su kien tinh tu 0
    // event_id la ma su kien
    int i = 0;
    int event_id = 0;
    //// tao cac opponent
    MadBear* madbear = new MadBear(0);
    Bandit* bandit = new Bandit(0);
    LordLupin* lordlupin = new LordLupin(0);
    Elf* elf = new Elf(0);
    Troll* troll = new Troll(0);
    Tornbery* tornbery = new Tornbery(0);
    NinaDeRings* ninaderings = new NinaDeRings;
    QueenOfCards* queenofcards = new QueenOfCards(0);
    DurianGarden* duriangarden = new DurianGarden;
    OmegaWeapon* omegaweapon = new OmegaWeapon;
    Hades* hades = new Hades;
    /////// in for loop
    for (i = 0; i < events->count(); i++)
    {
        BaseKnight* current_knight = this->lastKnight();///
      

        event_id = events->get(i);
        if (event_id != 99) {
            switch (event_id) {
            case 1: {
                madbear->set_levelO(i);
                if (this->fight(madbear))
                {

                };
                break;
            }
            case 2: {
                bandit->set_levelO(i);
                if (this->fight(bandit))
                {

                };
                break;
            }
            case 3: {
                lordlupin->set_levelO(i);
                if (this->fight(lordlupin))
                {

                };
                break;
            }
            case 4: {
                elf->set_levelO(i);
                if (this->fight(elf))
                {

                };
                break;
            }
            case 5: {
                troll->set_levelO(i);
                if (this->fight(troll))
                {

                };
                break;
            }

                  ///////////////////////
                  ///////////////////////

            case 6: {
                tornbery->set_levelO(i);
                if (this->fight(tornbery))// da hoi mau
                {
                    this->lastKnight()->Set_Level(this->lastKnight()->Get_Level() + 1);
                }
                else
                {
                    if (this->lastKnight()->Get_Knight_Type() != DRAGON) {
                        this->lastKnight()->Poisonous(true);
                    } //hiep si ko phai dragon bi trung doc
                    Antidote antidote;
                    if (antidote.canUse(this->lastKnight())) {
                        //  cout << "sai duoc" << endl;
                        antidote.use(this->lastKnight());
                    }
                    if (this->lastKnight()->IsPoisonous()) {
                        this->lastKnight()->Get_Bag()->drop_items();
                        this->lastKnight()->Poisonous(false);
                        this->lastKnight()->Set_HP(this->lastKnight()->Get_HP() - 10);
                        this->Healing();
                    }
                }
                break;
            }
            case 7: {
                queenofcards->set_levelO(i);
                if (this->fight(queenofcards)) { this->Add_Gil(this->lastKnight()->Get_Gil() * 2); }
                else {
                    if (this->lastKnight()->Get_Knight_Type() != PALADIN)
                    {
                        Add_Gil(this->lastKnight()->Get_Gil() / 2);
                    }
                }
                break;
            }
            case 8: {
                if (((this->lastKnight()->Get_Gil() >= 50) || this->lastKnight()->Get_Knight_Type() == PALADIN) &&
                    this->lastKnight()->Get_HP() < (this->lastKnight()->Get_MaxHP()) / 3) {
                    this->lastKnight()->Set_HP((this->lastKnight()->Get_MaxHP() / 5) + this->lastKnight()->Get_HP());
                    if (this->lastKnight()->Get_Knight_Type() != PALADIN)
                    {
                        this->lastKnight()->Set_Gil(this->lastKnight()->Get_Gil() - 50);
                    }
                }
                break;
            }
            case 9: {
                for (int i = (this->army_count) - 1; i >= 0; i--)
                {
                    this->army[i]->Set_HP(this->army[i]->Get_MaxHP());
                }
                break;
            }
            case 10: {
                while (omegaweapon->get_meet_omegaweapon() == false)
                {
                    if (this->lastKnight() != nullptr) {
                        if (this->lastKnight()->Get_Knight_Type() == DRAGON
                            || ((this->lastKnight()->Get_Level() == 10)
                                && this->lastKnight()->Get_HP() == this->lastKnight()->Get_MaxHP())) {
                            this->lastKnight()->Set_Level(10);
                            this->lastKnight()->Set_Gil(999);
                            omegaweapon->set_omegaweapon();
                            break;

                        }
                        else {
                            this->lastKnight()->Set_HP(0);
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                this->Healing();
                break;
            }
            case 11: {
                while (hades->get_meet_hades() == false)
                {
                    if (this->lastKnight() != nullptr) {
                        if (((this->lastKnight()->Get_Knight_Type() == PALADIN) && (this->lastKnight()->Get_Level() >= 8))
                            || ((this->lastKnight()->Get_Level() == 10))) {
                            hades->set_meet_hades();
                            this->set_shield(); 
                            break;
                        }
                        else {
                            this->lastKnight()->Set_HP(0);
                            break;
                        }
                    }
                }
                this->Healing();
                break;
            }
                   ///////////////////////
                   ///////////////////////
            case 95: {
                this->set_shield();
                break;
            }
            case 96: {
                this->set_spear();
                break;
            }
            case 97: {
                this->set_hair();
                break;
            }
            case 98: {
                if (this->hasPaladinShield() &&
                    this->hasLancelotSpear() &&
                    this->hasGuinevereHair()) {
                    this->set_sword();
                }
                break;
            }
            case 112: {
                PhoenixDownII* phoenixdown2 = new PhoenixDownII();
                if (this->count() >= 1) {
                    int k = this->count() - 1;
                    for (k; k >= 0; k--)
                    {
                        if (this->get_knight(k)->Get_Bag()->insertFirst(phoenixdown2) == true) { break; };
                    }
                }
                break;
            }
            case 113: {
                PhoenixDownIII* phoenixdown3 = new PhoenixDownIII();
                if (this->count() >= 1) {
                    int k = this->count() - 1;
                    for (k; k >= 0; k--)
                    {
                        if (this->get_knight(k)->Get_Bag()->insertFirst(phoenixdown3) == true) { break; };
                    }
                }
                break;
            }
            case 114: {
                PhoenixDownIV* phoenixdown4 = new PhoenixDownIV();
                if (this->count() >= 1) {
                    int k = this->count() - 1;
                    for (k; k >= 0; k--)
                    {
                        if (this->get_knight(k)->Get_Bag()->insertFirst(phoenixdown4) == true) { break; };
                    }
                }
                break;
            }
            }
            this->printInfo();
            if ((i == events->count()-1)|| this->lastKnight() == nullptr) {
                if (this->lastKnight() != nullptr  ) {
                    this->set_defeat_ultimecia();
                    return defeat_ultimecia;
                }
                else{return defeat_ultimecia;}
            }
        }
        ///////////////////////
        else {
            ///code ultimecia
            {
                if (this->hasExcaliburSword())
                {
                    this->set_defeat_ultimecia();
                }
                else if (this->hasPaladinShield() &&
                    this->hasLancelotSpear() &&
                    this->hasGuinevereHair()) 
                     {
                        int ultimecia_hp = 5000;
                        if (this->count() >= 1) {
                            int k = this->count() - 1;
                            for (k; k >= 0; k--)
                            {
                                if (this->get_knight(k)->Get_Knight_Type() == NORMAL) {
                                continue;
                            }
                                else {
                                double base_damage_knight = this->get_knight(k)->Get_BaseDamage();
                                int hp_knight = this->get_knight(k)->Get_HP();
                                int level_knight = this->get_knight(k)->Get_Level();

                                int damage = int(base_damage_knight * hp_knight * level_knight);

                                ultimecia_hp -= damage;

                                if (ultimecia_hp <= 0) {
                                    this->set_defeat_ultimecia();
                                    break;
                                }
                                else
                                {
                                    this->set_army(this->get_knight(k));
                                }
                            }
                            }
                        }
                        if (ultimecia_hp > 0) {
                            this->Delete_Army();
                        };
                     }
                else
                {
                    this->Delete_Army();
                }  
            }    
            this->printInfo();
            return defeat_ultimecia;
        }
        ///// out of for loop
    }
};

void ArmyKnights::set_count(int count) {army_count = count;};

int ArmyKnights::count() const {return army_count;};

BaseKnight* ArmyKnights::lastKnight() const {
    if (army_count == 0) {
        return nullptr;
    }
    else {
        int a = army_count - 1;
        return army[a];
    }
};

bool ArmyKnights::hasPaladinShield() const {return have_shield;};

bool ArmyKnights::hasLancelotSpear() const {return have_spear;};

bool ArmyKnights::hasGuinevereHair() const {return have_hair;};

bool ArmyKnights::hasExcaliburSword() const {return have_sword;};

bool ArmyKnights::defeated_ultimecia()const {return defeat_ultimecia;};

void ArmyKnights::set_shield() {have_shield = true;};

void ArmyKnights::set_spear() {have_spear = true;};

void ArmyKnights::set_hair() {have_hair = true;};

void ArmyKnights::set_sword() {have_sword = true;};

void ArmyKnights::set_defeat_ultimecia() {defeat_ultimecia = true;};

BaseKnight* ArmyKnights::get_knight(int knight_index) {return army[knight_index];};

void ArmyKnights::Delete_Army() {
    delete army;
    army = nullptr;
    set_count(0);
};

void ArmyKnights::set_army(BaseKnight* dead_knight) {
    for (int i = 0; i < count(); i++) {
        if (army[i] == dead_knight) {
            delete army[i];
            army[i] = nullptr;
            // xóa dead_knight ra khỏi army
            // Di chuyển các phần tử sau nó sang trái
            for (int j = i; j < count() - 1; j++) {
                army[j] = army[j + 1];
            }
            // Giảm kích thước của mảng
            set_count(count() - 1);
            // Giảm chỉ số để không bỏ qua phần tử nào
            i--;
        }
    }
};

/* * * END implementation of class ArmyKnights * * */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* * * BEGIN implementation of class Events * * */

Events::Events(const string& file_events) {
    ifstream input_events;
    input_events.open(file_events);
    input_events >> event_count;
    p_event = new int[event_count];
    for (int i = 0; i < event_count; i++) {
        input_events >> p_event[i];
    }
    input_events.close();
}

int Events::count() const {return event_count;};

int Events::get(int i) const {return p_event[i];};

Events::~Events() {
    delete p_event;
    p_event = nullptr;
};

/* * * END implementation of class Events * * */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
};

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    armyKnights = nullptr;
    delete events;
    events = nullptr;
};

void KnightAdventure::loadArmyKnights(const string& file_armyknights) {armyKnights = new ArmyKnights(file_armyknights);};

void KnightAdventure::loadEvents(const string& file_event) {events = new Events(file_event);};

void KnightAdventure::run() { armyKnights->printResult(armyKnights->adventure(events)); }
/* * * END implementation of class KnightAdventure * * */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
