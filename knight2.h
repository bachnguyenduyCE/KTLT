#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"


// #define DEBUG

enum ItemType { ANTIDOTE, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV };

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BaseKnight;

class BaseItem {

public:
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    virtual ItemType getType() const = 0;

};

class Antidote :public BaseItem {
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType getType() const;      
};

class PhoenixDownI :public BaseItem {
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType getType() const;
};

class PhoenixDownII :public BaseItem {
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType getType() const;
};

class PhoenixDownIII :public BaseItem {
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType getType() const;
};

class PhoenixDownIV : public BaseItem {
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType getType() const;
};

class BaseBag {
protected:
    struct Node {
        BaseItem* item;
        Node* next;

        Node(BaseItem* item) {
            this->item = item;
            this->next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;
    int max_size;
public:
    BaseBag();

    virtual bool insertFirst(BaseItem* item);

    virtual BaseItem* get(ItemType itemType);

    virtual string toString() const;

    void drop_items();

    void find_phoenix(BaseKnight* knight_own);
}; //ok

class PaladinBag : public BaseBag {
public:
    PaladinBag(int phoenixdownI_a, int antidote_b){  
        // Thêm các PhoenixDown loại I vào đầu danh sách liên kết
        for (int i = 0; i < phoenixdownI_a; i++) {
            PhoenixDownI* phoenixDown = new PhoenixDownI();
            insertFirst(phoenixDown);
        }
        // Thêm các Antidote vào đầu danh sách liên kết
        for (int j = 0; j < antidote_b; j++) {
            Antidote* antidote = new Antidote();
            insertFirst(antidote);
        }
    }
    bool insertFirst(BaseItem* item) {
        Node* node = new Node(item);
        if (size == 0) {
            head = node;
            tail = node;
        }
        else {
            node->next = head;
       //     head->prev = node;
            head = node;
        }
        size++;

        return true;
    }
}; //ok

class LancelotBag : public BaseBag {
public:
    LancelotBag(int phoenixdownI_a, int antidote_b) {
        // set maxsize
        max_size = 16;
        // Thêm các PhoenixDown loại I vào đầu danh sách liên kết
        for (int i = 0; i < phoenixdownI_a; i++) {
            PhoenixDownI* phoenixDown = new PhoenixDownI();
            insertFirst(phoenixDown);
        }
        // Thêm các Antidote vào đầu danh sách liên kết
        for (int j = 0; j < antidote_b; j++) {
            Antidote* antidote = new Antidote();
            insertFirst(antidote);
        }
    }
}; //ok

class DragonBag : public BaseBag {
public:
    DragonBag( int phoenixdownI_a, int antidote_b) {
        // set maxsize
        max_size = 14;
        // Thêm các PhoenixDown loại I vào đầu danh sách liên kết
        for (int i = 0; i < phoenixdownI_a; i++) {
            PhoenixDownI* phoenixDown = new PhoenixDownI();
            insertFirst(phoenixDown);
        }
        // Thêm các Antidote vào đầu danh sách liên kết
        for (int j = 0; j < antidote_b; j++) {
            Antidote* antidote = new Antidote();
            insertFirst(antidote);
        }
    }
    bool insertFirst(BaseItem* item) {
        if (size >= max_size) {
            return false;
        }

        if (item->getType()==ANTIDOTE)
        {
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

}; //ok

class NormalBag : public BaseBag {
public:
    NormalBag(int phoenixdownI_a, int antidote_b){
        // set maxsize
        max_size = 19;
        // Thêm các PhoenixDown loại I vào đầu danh sách liên kết
        for (int i = 0; i < phoenixdownI_a; i++) {
            PhoenixDownI* phoenixDown = new PhoenixDownI();
            insertFirst(phoenixDown);
        }
        // Thêm các Antidote vào đầu danh sách liên kết
        for (int j = 0; j < antidote_b; j++) {
            Antidote* antidote = new Antidote();
            insertFirst(antidote);
        }
    }
}; //ok

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BaseOpponent {
protected:
    int BaseDamage;
    int BaseGil;
    int levelO;
    int id;
public:
    BaseOpponent(){
        BaseDamage = 0;
        BaseGil=0;
        levelO=0;
        id=0;
    };
    void set_levelO(int i) {
         levelO = (i + id) % 10 + 1;
    };
    int get_levelO() {
        return levelO;
    };
    int get_BaseGil() {
        return BaseGil;
    };
    int get_BaseDamage() {
        return BaseDamage;
    };
    int get_id() {
        return id;
    };
    ~BaseOpponent();

};

class MadBear : public BaseOpponent {
public:
    MadBear(int i) {
        id = 1;
        BaseDamage = 10;
        BaseGil = 100;
        levelO = (i + id) % 10 + 1;
    };
    ~MadBear(){};
};

class Bandit : public BaseOpponent {
public:
    Bandit(int i) {
        id = 2;
        BaseDamage = 15;
        BaseGil = 150;
        levelO = (i + id) % 10 + 1;
    };
    ~Bandit(){};
};

class LordLupin : public BaseOpponent {
public:
    LordLupin(int i) {
        id = 3;
        BaseDamage = 45;
        BaseGil = 450;
        levelO = (i + id) % 10 + 1;
    };
    ~LordLupin(){};
};

class Elf : public BaseOpponent {
public:
    Elf(int i) {
        id = 4;
        BaseDamage = 75;
        BaseGil = 750;
        levelO = (i + id) % 10 + 1;
    };
    ~Elf(){};
};

class Troll : public BaseOpponent {
public:
    Troll(int i) {
        id = 5;
        BaseDamage = 95;
        BaseGil = 800;
        levelO = (i + id) % 10 + 1;
    };
    ~Troll(){};
};

class Tornbery : public BaseOpponent {
public:
    Tornbery(int i) {
        id = 6;
        BaseDamage = 0;
        BaseGil = 0;
        levelO = (i + id) % 10 + 1;
    };
    ~Tornbery(){};
};

class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards(int i) {
        id = 7;
        BaseDamage = 0;
        BaseGil = 0;
        levelO = (i + id) % 10 + 1;
    };
    ~QueenOfCards(){};
};

class NinaDeRings : public BaseOpponent {
public:
    NinaDeRings() {
        id = 8;
        BaseDamage = 0;
        BaseGil = 0;
    };
    ~NinaDeRings(){};
};

class DurianGarden : public BaseOpponent {
public:
    DurianGarden() {
        id = 9;
        BaseDamage = 0;
        BaseGil = 0;
    };
    ~DurianGarden(){};
};

class OmegaWeapon : public BaseOpponent {
protected:
    bool defeat_omegaweapon;
public:
    OmegaWeapon() {
        id = 10;
        BaseDamage = 0;
        BaseGil = 0;
        defeat_omegaweapon = false;
    };
    void set_omegaweapon() {
        defeat_omegaweapon = 1;
    };
    bool get_meet_omegaweapon() {
        return defeat_omegaweapon;
    };
    ~OmegaWeapon();
};

class Hades : public BaseOpponent {
protected:
    bool defeat_hades;
public:
    Hades() {
        id = 11;
        BaseDamage = 0;
        BaseGil = 0;
        defeat_hades = 0;
    };
    void set_meet_hades() {
        defeat_hades = 1;
    };
    bool get_meet_hades() {
        return defeat_hades;
    };
    ~Hades(){};
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
    bool poisonous;


public:

    BaseKnight();
    void Poisonous(bool poison);
    bool IsPoisonous();
    void Set_HP(int new_HP);
    void Set_Level(int new_level);
    void Set_Gil(int new_gil);
    BaseBag* Get_Bag();
    KnightType Get_Knight_Type();
    double Get_BaseDamage();
    int Get_HP();
    int Get_MaxHP();
    int Get_Level();
    int Get_Gil();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~PaladinKnight();
};

class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~LancelotKnight();
}; 

class DragonKnight : public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~DragonKnight();
}; 

class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~NormalKnight();
}; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Events {
    int* p_event = nullptr;
    int event_count = 0; 

public:
    Events(const string& file_events); //ok
    int count() const; //ok
    int get(int i) const; //ok
    ~Events(); //ok
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArmyKnights {
protected:
    int army_count=0;
    BaseKnight** army; // mảng lưu đia chỉ của các hiệp sĩ
    bool have_shield = false;
    bool have_spear = false;
    bool have_hair = false;
    bool have_sword = false;
    bool defeat_ultimecia = false;
public:
    ArmyKnights (const string & file_armyknights); //ok
    ~ArmyKnights(); //ok
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);

    void set_count(int count);
    int count() const; //ok
    BaseKnight * lastKnight() const; //ok
    

    bool hasPaladinShield() const; //ok
    bool hasLancelotSpear() const; //ok
    bool hasGuinevereHair() const; //ok
    bool hasExcaliburSword() const; //ok
    bool defeated_ultimecia()const ; //ok


    void set_shield(); //ok
    void set_spear(); //ok
    void set_hair(); //ok
    void set_sword(); //ok
    void set_defeat_ultimecia(); //ok

    BaseKnight* get_knight(int i);
    void set_army(BaseKnight* dead_knight);
    void Delete_Army();
    void Add_Gil(int new_gil);
    void Healing();

    void printInfo() const; //ok
    void printResult(bool win) const; // ok
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure(); //
    ~KnightAdventure(); // TODO: //ok

    void loadArmyKnights(const string &); //ok
    void loadEvents(const string &); //ok
    void run();
};

#endif // __KNIGHT2_H__