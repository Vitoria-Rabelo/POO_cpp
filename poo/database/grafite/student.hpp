#pragma once
#include "fn.hpp"

class Lead {
private:
    float thickness{0};
    std::string hardness;
    int size{0};

public:
    Lead(float thickness, const std::string hardness, int size)
        : thickness(thickness), hardness(hardness), size(size) {}

    float getThickness() const {
        return this->thickness;
    }

    int getSize() const {
        return this->size;
    }

    void setSize(int newSize) {
        this->size = newSize;
    }

    const std::string& getHardness() const {
        return this->hardness;
    }

    int usagePerSheet() const {
        if (hardness == "HB") {
            return 1;
        }
        if (hardness == "2B") {
            return 2;
        }
        if (hardness == "4B") {
            return 4;
        }
        if (hardness == "6B") {
            return 6;
        }
        return 0;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << this->thickness;
        return "[" + oss.str() + ":" + this->hardness + ":" + std::to_string(this->size) + "]";
    }
};

class Pencil {
private:
    float thickness{0};
    std::shared_ptr<Lead> tip{nullptr};

public:
    Pencil(float thickness) : thickness(thickness), tip(nullptr) {}

    bool hasLead() const {
        if (tip == nullptr) {
            return false;
        }
        return true;
    }

    void insert(std::shared_ptr<Lead> lead) {
        if (this->hasLead()) {
            fn::write("fail: ja existe grafite");
            return;
        }
        if (lead->getThickness() != this->thickness) {
            fn::write("fail: calibre incompativel");
            return;
        }
        this->tip = lead;
    }

    std::shared_ptr<Lead> remove() {
        if (this->tip == nullptr) {
            fn::write("fail: nao existe grafite");
            return nullptr;
        }
        std::shared_ptr<Lead> removed = this->tip;
        this->tip = nullptr;
        return removed;
    }

    void writePage() {
        if (this->tip == nullptr) {
            fn::write("fail: nao existe grafite");
            return;
        }

        if (this->tip->getSize() <= 10) {
            fn::write("fail: tamanho insuficiente");
            return;
        }

        int usage = this->tip->usagePerSheet();
        if (this->tip->getSize() < usage + 10) {
            fn::write("fail: folha incompleta");
            this->tip->setSize(10);
            return;
        }

        this->tip->setSize(this->tip->getSize() - usage);
    }

    std::string toString() const {
        std::string leadInfo = "null";
        if (this->tip != nullptr) {
            leadInfo = this->tip->toString();
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << this->thickness;
        return "calibre: " + oss.str() + ", grafite: " + leadInfo;
    }
};

class Student {
private:
    Pencil pencil;

public:
    Student(float thickness) : pencil(thickness) {}

    void insert(float thickness, std::string hardness, int length) {
        pencil.insert(std::make_shared<Lead>(thickness, hardness, length));
    }

    void remove() {
        pencil.remove();
    }

    void writePage() {
        pencil.writePage();
    }

    void show() {
        std::cout << pencil.toString() << std::endl;
    }
};
