#include <gtkmm.h>
#include <sstream>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include "Functional.hpp"

class MainWindow : public Gtk::Window {
private:
    MutableArraySequence<int> arraySeq;
    ListSequence<int> listSeq;
    MutableArraySequence<int> mutableSeq;
    ImmutableArraySequence<int> immutableSeq;
    BitSequence bitSeq1;
    ArraySequence<int> seq1;
    ArraySequence<int> seq2;
    
    Gtk::Box mainBox;
    Gtk::Notebook notebook;
    
    Gtk::Box arrayPage;
    Gtk::Box listPage;
    Gtk::Box mutablePage;
    Gtk::Box immutablePage;
    Gtk::Box bitPage;
    Gtk::Box funcPage;
    
    Gtk::Box arrayTopBox;
    Gtk::Box arrayBottomBox;
    Gtk::Box listTopBox;
    Gtk::Box listBottomBox;
    Gtk::Box mutableTopBox;
    Gtk::Box mutableBottomBox;
    Gtk::Box immutableTopBox;
    Gtk::Box immutableBottomBox;
    Gtk::Box bitTopBox;
    Gtk::Box bitBottomBox;
    Gtk::Box funcBox;
    Gtk::Box seq1Box;
    Gtk::Box seq2Box;
    Gtk::Box funcButtonsBox;
    
    Gtk::Button arrayAppendButton;
    Gtk::Button arrayPrependButton;
    Gtk::Button arrayInsertButton;
    Gtk::Button arrayGetButton;
    Gtk::Button arrayConcatButton;
    Gtk::Button arraySubseqButton;
    Gtk::Button arrayClearButton;
    
    Gtk::Button listAppendButton;
    Gtk::Button listPrependButton;
    Gtk::Button listInsertButton;
    Gtk::Button listGetButton;
    Gtk::Button listConcatButton;
    Gtk::Button listSubseqButton;
    Gtk::Button listClearButton;
    
    Gtk::Button mutableAppendButton;
    Gtk::Button mutablePrependButton;
    Gtk::Button mutableInsertButton;
    
    Gtk::Button immutableAppendButton;
    Gtk::Button immutablePrependButton;
    Gtk::Button immutableInsertButton;
    
    Gtk::Button bitSetButton;
    Gtk::Button bitAndButton;
    Gtk::Button bitOrButton;
    Gtk::Button bitXorButton;
    Gtk::Button bitNotButton;
    
    Gtk::Button mapButton;
    Gtk::Button whereButton;
    Gtk::Button reduceButton;
    Gtk::Button zipButton;
    Gtk::Button seq1AddButton;
    Gtk::Button seq1ClearButton;
    Gtk::Button seq2AddButton;
    Gtk::Button seq2ClearButton;

    Gtk::Entry arrayValueEntry;
    Gtk::Entry arrayIndexEntry;
    Gtk::Entry listValueEntry;
    Gtk::Entry listIndexEntry;
    Gtk::Entry mutableValueEntry;
    Gtk::Entry immutableValueEntry;
    Gtk::Entry immutableIndexEntry;
    Gtk::Entry bitIndexEntry;
    Gtk::Entry bitValueEntry;
    Gtk::Entry bitSizeEntry;
    Gtk::Entry seq1Entry;
    Gtk::Entry seq2Entry;
    
    Gtk::ScrolledWindow arrayScroll;
    Gtk::ScrolledWindow listScroll;
    Gtk::ScrolledWindow mutableScroll;
    Gtk::ScrolledWindow immutableScroll;
    Gtk::ScrolledWindow bitScroll;
    Gtk::ScrolledWindow funcScroll;
    
    Gtk::TextView arrayOutput;
    Gtk::TextView listOutput;
    Gtk::TextView mutableOutput;
    Gtk::TextView immutableOutput;
    Gtk::TextView bitOutput;
    Gtk::TextView funcOutput;
    
    Glib::RefPtr<Gtk::TextBuffer> arrayBuffer;
    Glib::RefPtr<Gtk::TextBuffer> listBuffer;
    Glib::RefPtr<Gtk::TextBuffer> mutableBuffer;
    Glib::RefPtr<Gtk::TextBuffer> immutableBuffer;
    Glib::RefPtr<Gtk::TextBuffer> bitBuffer;
    Glib::RefPtr<Gtk::TextBuffer> funcBuffer;
    
    void appendArrayOutput(const Glib::ustring& text) {
        auto iter = arrayBuffer->end();
        arrayBuffer->insert(iter, text + "\n");
    }
    
    void appendListOutput(const Glib::ustring& text) {
        auto iter = listBuffer->end();
        listBuffer->insert(iter, text + "\n");
    }
    
    void appendMutableOutput(const Glib::ustring& text) {
        auto iter = mutableBuffer->end();
        mutableBuffer->insert(iter, text + "\n");
    }
    
    void appendImmutableOutput(const Glib::ustring& text) {
        auto iter = immutableBuffer->end();
        immutableBuffer->insert(iter, text + "\n");
    }
    
    void appendBitOutput(const Glib::ustring& text) {
        auto iter = bitBuffer->end();
        bitBuffer->insert(iter, text + "\n");
    }
    
    void appendFuncOutput(const Glib::ustring& text) {
        auto iter = funcBuffer->end();
        funcBuffer->insert(iter, text + "\n");
    }
    
    Glib::ustring getSequenceString(Sequence<int>* seq) {
        Glib::ustring result = "[";
        for (int i = 0; i < seq->GetLength(); ++i) {
            result += std::to_string(seq->Get(i));
            if (i < seq->GetLength() - 1) result += ", ";
        }
        result += "]";
        return result;
    }
    
    Glib::ustring getBitString(BitSequence* seq) {
        Glib::ustring result = "";
        for (int i = 0; i < seq->GetLength(); ++i) {
            result += seq->Get(i) ? "1" : "0";
        }
        return result;
    }
    
    void onArrayAppend() {
        try {
            int value = std::stoi(arrayValueEntry.get_text());
            arraySeq.Append(value);
            appendArrayOutput("Добавить " + std::to_string(value) + ": " + getSequenceString(&arraySeq));
            arrayValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendArrayOutput("Ошибка: введите число");
        }
    }
    
    void onArrayPrepend() {
        try {
            int value = std::stoi(arrayValueEntry.get_text());
            arraySeq.Prepend(value);
            appendArrayOutput("Добавить в начало " + std::to_string(value) + ": " + getSequenceString(&arraySeq));
            arrayValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendArrayOutput("Ошибка: введите число");
        }
    }
    
    void onArrayInsert() {
        try {
            int index = std::stoi(arrayIndexEntry.get_text());
            int value = std::stoi(arrayValueEntry.get_text());
            arraySeq.InsertAt(value, index);
            appendArrayOutput("Вставить " + std::to_string(value) + " в " + std::to_string(index) + ": " + getSequenceString(&arraySeq));
            arrayIndexEntry.set_text("");
            arrayValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendArrayOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onArrayGet() {
        try {
            int index = std::stoi(arrayIndexEntry.get_text());
            int value = arraySeq.Get(index);
            appendArrayOutput("Получить[" + std::to_string(index) + "] = " + std::to_string(value));
            arrayIndexEntry.set_text("");
        } catch (const std::exception& e) {
            appendArrayOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onArrayConcat() {
        MutableArraySequence<int> seq2;
        seq2.Append(100);
        seq2.Append(200);
        seq2.Append(300);
        Sequence<int>* result = arraySeq.Concat(seq2);
        appendArrayOutput("Склеить с [100,200,300]: " + getSequenceString(result));
        delete result;
    }
    
    void onArraySubseq() {
        try {
            int start = std::stoi(arrayIndexEntry.get_text());
            Sequence<int>* subseq = arraySeq.GetSubsequence(start, arraySeq.GetLength() - 1);
            appendArrayOutput("Подпоследовательность с " + std::to_string(start) + ": " + getSequenceString(subseq));
            delete subseq;
            arrayIndexEntry.set_text("");
        } catch (const std::exception& e) {
            appendArrayOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onArrayClear() {
        while (arraySeq.GetLength() > 0) {
            arraySeq.RemoveAt(0);
        }
        appendArrayOutput("Очистить: " + getSequenceString(&arraySeq));
    }
    
    void onListAppend() {
        try {
            int value = std::stoi(listValueEntry.get_text());
            listSeq.Append(value);
            appendListOutput("Добавить " + std::to_string(value) + ": " + getSequenceString(&listSeq));
            listValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendListOutput("Ошибка: введите число");
        }
    }
    
    void onListPrepend() {
        try {
            int value = std::stoi(listValueEntry.get_text());
            listSeq.Prepend(value);
            appendListOutput("Добавить в начало " + std::to_string(value) + ": " + getSequenceString(&listSeq));
            listValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendListOutput("Ошибка: введите число");
        }
    }
    
    void onListInsert() {
        try {
            int index = std::stoi(listIndexEntry.get_text());
            int value = std::stoi(listValueEntry.get_text());
            listSeq.InsertAt(value, index);
            appendListOutput("Вставить " + std::to_string(value) + " в " + std::to_string(index) + ": " + getSequenceString(&listSeq));
            listIndexEntry.set_text("");
            listValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendListOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onListGet() {
        try {
            int index = std::stoi(listIndexEntry.get_text());
            int value = listSeq.Get(index);
            appendListOutput("Получить[" + std::to_string(index) + "] = " + std::to_string(value));
            listIndexEntry.set_text("");
        } catch (const std::exception& e) {
            appendListOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onListConcat() {
        ListSequence<int> seq2;
        seq2.Append(100);
        seq2.Append(200);
        seq2.Append(300);
        Sequence<int>* result = listSeq.Concat(seq2);
        appendListOutput("Склеить с [100,200,300]: " + getSequenceString(result));
        delete result;
    }
    
    void onListSubseq() {
        try {
            int start = std::stoi(listIndexEntry.get_text());
            Sequence<int>* subseq = listSeq.GetSubsequence(start, listSeq.GetLength() - 1);
            appendListOutput("Подпоследовательность с " + std::to_string(start) + ": " + getSequenceString(subseq));
            delete subseq;
            listIndexEntry.set_text("");
        } catch (const std::exception& e) {
            appendListOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onListClear() {
        while (listSeq.GetLength() > 0) {
            listSeq.RemoveAt(0);
        }
        appendListOutput("Очистить: " + getSequenceString(&listSeq));
    }
    
    void onMutableAppend() {
        try {
            int value = std::stoi(mutableValueEntry.get_text());
            mutableSeq.Append(value);
            appendMutableOutput("Mutable Добавить " + std::to_string(value) + ": " + getSequenceString(&mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendMutableOutput("Ошибка: введите число");
        }
    }
    
    void onMutablePrepend() {
        try {
            int value = std::stoi(mutableValueEntry.get_text());
            mutableSeq.Prepend(value);
            appendMutableOutput("Mutable Добавить в начало " + std::to_string(value) + ": " + getSequenceString(&mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendMutableOutput("Ошибка: введите число");
        }
    }
    
    void onMutableInsert() {
        try {
            int index = std::stoi(mutableValueEntry.get_text());
            int value = std::stoi(mutableValueEntry.get_text());
            mutableSeq.InsertAt(value, index);
            appendMutableOutput("Mutable Вставить " + std::to_string(value) + " в " + std::to_string(index) + ": " + getSequenceString(&mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendMutableOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onImmutableAppend() {
        try {
            int value = std::stoi(immutableValueEntry.get_text());
            ImmutableArraySequence<int>* newSeq = immutableSeq.AppendImmutable(value);
            appendImmutableOutput("Immutable Добавить " + std::to_string(value));
            appendImmutableOutput("  Было: " + getSequenceString(&immutableSeq));
            appendImmutableOutput("  Стало: " + getSequenceString(newSeq));
            delete newSeq;
            immutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendImmutableOutput("Ошибка: введите число");
        }
    }
    
    void onImmutablePrepend() {
        try {
            int value = std::stoi(immutableValueEntry.get_text());
            ImmutableArraySequence<int>* newSeq = immutableSeq.PrependImmutable(value);
            appendImmutableOutput("Immutable Добавить в начало " + std::to_string(value));
            appendImmutableOutput("  Было: " + getSequenceString(&immutableSeq));
            appendImmutableOutput("  Стало: " + getSequenceString(newSeq));
            delete newSeq;
            immutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendImmutableOutput("Ошибка: введите число");
        }
    }
    
    void onImmutableInsert() {
        try {
            int index = std::stoi(immutableIndexEntry.get_text());
            int value = std::stoi(immutableValueEntry.get_text());
            ImmutableArraySequence<int>* newSeq = immutableSeq.InsertAtImmutable(value, index);
            appendImmutableOutput("Immutable Вставить " + std::to_string(value) + " в " + std::to_string(index));
            appendImmutableOutput("  Было: " + getSequenceString(&immutableSeq));
            appendImmutableOutput("  Стало: " + getSequenceString(newSeq));
            delete newSeq;
            immutableIndexEntry.set_text("");
            immutableValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendImmutableOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onBitSet() {
        try {
            int index = std::stoi(bitIndexEntry.get_text());
            int value = std::stoi(bitValueEntry.get_text());
            if (bitSeq1.GetLength() <= index) {
                BitSequence newSeq(index + 1);
                for (int i = 0; i < bitSeq1.GetLength(); ++i) {
                    newSeq.Set(i, bitSeq1.Get(i));
                }
                bitSeq1 = newSeq;
            }
            bitSeq1.Set(index, value == 1);
            appendBitOutput("BitSequence1: " + getBitString(&bitSeq1));
            bitIndexEntry.set_text("");
            bitValueEntry.set_text("");
        } catch (const std::exception& e) {
            appendBitOutput("Ошибка: введите корректные данные");
        }
    }
    
    void onBitAnd() {
        try {
            int size = std::stoi(bitSizeEntry.get_text());
            BitSequence seq2(size);
            for (int i = 0; i < size && i < bitSeq1.GetLength(); ++i) {
                seq2.Set(i, bitSeq1.Get(i));
            }
            BitSequence result = bitSeq1 & seq2;
            appendBitOutput("BitSequence1 И BitSequence2: " + getBitString(&result));
        } catch (const std::exception& e) {
            appendBitOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onBitOr() {
        try {
            int size = std::stoi(bitSizeEntry.get_text());
            BitSequence seq2(size);
            for (int i = 0; i < size && i < bitSeq1.GetLength(); ++i) {
                seq2.Set(i, bitSeq1.Get(i));
            }
            BitSequence result = bitSeq1 | seq2;
            appendBitOutput("BitSequence1 ИЛИ BitSequence2: " + getBitString(&result));
        } catch (const std::exception& e) {
            appendBitOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onBitXor() {
        try {
            int size = std::stoi(bitSizeEntry.get_text());
            BitSequence seq2(size);
            for (int i = 0; i < size && i < bitSeq1.GetLength(); ++i) {
                seq2.Set(i, bitSeq1.Get(i));
            }
            BitSequence result = bitSeq1 ^ seq2;
            appendBitOutput("BitSequence1 ИСКЛЮЧАЮЩЕЕ ИЛИ BitSequence2: " + getBitString(&result));
        } catch (const std::exception& e) {
            appendBitOutput("Ошибка: " + Glib::ustring(e.what()));
        }
    }
    
    void onBitNot() {
        BitSequence result = ~bitSeq1;
        appendBitOutput("НЕ BitSequence1: " + getBitString(&result));
    }
    
    void onMap() {
        if (seq1.GetLength() == 0) {
            appendFuncOutput("Ошибка: первая последовательность пуста");
            return;
        }
        Sequence<int>* result = Functional<int, int>::Map(&seq1, [](int x) { return x * x; });
        appendFuncOutput("Map " + getSequenceString(&seq1) + " -> квадраты: " + getSequenceString(result));
        delete result;
    }
    
    void onWhere() {
        if (seq1.GetLength() == 0) {
            appendFuncOutput("Ошибка: первая последовательность пуста");
            return;
        }
        Sequence<int>* result = Functional<int, int>::Where(&seq1, [](int x) { return x % 2 == 0; });
        appendFuncOutput("Where " + getSequenceString(&seq1) + " -> четные: " + getSequenceString(result));
        delete result;
    }
    
    void onReduce() {
        if (seq1.GetLength() == 0) {
            appendFuncOutput("Ошибка: первая последовательность пуста");
            return;
        }
        int sum = Functional<int, int>::Reduce(&seq1, [](int acc, int x) { return acc + x; }, 0);
        int product = Functional<int, int>::Reduce(&seq1, [](int acc, int x) { return acc * x; }, 1);
        appendFuncOutput("Reduce " + getSequenceString(&seq1) + " -> сумма = " + std::to_string(sum) + ", произведение = " + std::to_string(product));
    }
    
    void onZip() {
        if (seq1.GetLength() == 0) {
            appendFuncOutput("Ошибка: первая последовательность пуста");
            return;
        }
        if (seq2.GetLength() == 0) {
            appendFuncOutput("Ошибка: вторая последовательность пуста");
            return;
        }
        Sequence<std::pair<int, int>>* result = Functional<int, int>::Zip(&seq1, &seq2);
        Glib::ustring zipStr = "[";
        for (int i = 0; i < result->GetLength(); ++i) {
            zipStr += "(" + std::to_string(result->Get(i).first) + "," + std::to_string(result->Get(i).second) + ")";
            if (i < result->GetLength() - 1) zipStr += ", ";
        }
        zipStr += "]";
        appendFuncOutput("Zip " + getSequenceString(&seq1) + " и " + getSequenceString(&seq2) + " -> " + zipStr);
        delete result;
    }
    
    void onSeq1Add() {
        std::string input = seq1Entry.get_text();
        std::stringstream ss(input);
        int num;
        while (ss >> num) {
            seq1.Append(num);
        }
        appendFuncOutput("Seq1 добавлены: " + getSequenceString(&seq1));
        seq1Entry.set_text("");
    }
    
    void onSeq1Clear() {
        while (seq1.GetLength() > 0) {
            seq1.RemoveAt(0);
        }
        appendFuncOutput("Seq1 очищена");
    }
    
    void onSeq2Add() {
        std::string input = seq2Entry.get_text();
        std::stringstream ss(input);
        int num;
        while (ss >> num) {
            seq2.Append(num);
        }
        appendFuncOutput("Seq2 добавлены: " + getSequenceString(&seq2));
        seq2Entry.set_text("");
    }
    
    void onSeq2Clear() {
        while (seq2.GetLength() > 0) {
            seq2.RemoveAt(0);
        }
        appendFuncOutput("Seq2 очищена");
    }
    
    Gtk::Label* makeLabel(const Glib::ustring& text) {
        return Gtk::make_managed<Gtk::Label>(text);
    }

public:
    MainWindow() : 
        mainBox(Gtk::ORIENTATION_VERTICAL, 5),
        arrayPage(),
        listPage(),
        mutablePage(),
        immutablePage(),
        bitPage(),
        funcPage(),
        arrayTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        arrayBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        listTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        listBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        mutableTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        mutableBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        immutableTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        immutableBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        bitTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        bitBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        funcBox(Gtk::ORIENTATION_VERTICAL, 10),
        seq1Box(Gtk::ORIENTATION_HORIZONTAL, 5),
        seq2Box(Gtk::ORIENTATION_HORIZONTAL, 5),
        funcButtonsBox(Gtk::ORIENTATION_HORIZONTAL, 5),
        arrayAppendButton("Добавить в конец"),
        arrayPrependButton("Добавить в начало"),
        arrayInsertButton("Вставить"),
        arrayGetButton("Получить"),
        arrayConcatButton("Склеить"),
        arraySubseqButton("Подпоследовательность"),
        arrayClearButton("Очистить"),
        listAppendButton("Добавить в конец"),
        listPrependButton("Добавить в начало"),
        listInsertButton("Вставить"),
        listGetButton("Получить"),
        listConcatButton("Склеить"),
        listSubseqButton("Подпоследовательность"),
        listClearButton("Очистить"),
        mutableAppendButton("Добавить в конец"),
        mutablePrependButton("Добавить в начало"),
        mutableInsertButton("Вставить"),
        immutableAppendButton("Добавить в конец"),
        immutablePrependButton("Добавить в начало"),
        immutableInsertButton("Вставить"),
        bitSetButton("Установить бит"),
        bitAndButton("И"),
        bitOrButton("ИЛИ"),
        bitXorButton("ИСКЛЮЧАЮЩЕЕ ИЛИ"),
        bitNotButton("НЕ"),
        mapButton("Map"),
        whereButton("Where"),
        reduceButton("Reduce"),
        zipButton("Zip"),
        seq1AddButton("Добавить в Seq1"),
        seq1ClearButton("Очистить Seq1"),
        seq2AddButton("Добавить в Seq2"),
        seq2ClearButton("Очистить Seq2"),
        arrayValueEntry(),
        arrayIndexEntry(),
        listValueEntry(),
        listIndexEntry(),
        mutableValueEntry(),
        immutableValueEntry(),
        immutableIndexEntry(),
        bitIndexEntry(),
        bitValueEntry(),
        bitSizeEntry(),
        seq1Entry(),
        seq2Entry() {
        
        set_title("Лабораторная работа 2");
        set_default_size(1000, 700);
        
        add(mainBox);
        
        notebook.set_hexpand(true);
        notebook.set_vexpand(true);
        mainBox.pack_start(notebook, Gtk::PACK_EXPAND_WIDGET, 5);
        
        arrayBuffer = Gtk::TextBuffer::create();
        arrayOutput.set_buffer(arrayBuffer);
        arrayOutput.set_editable(false);
        arrayScroll.add(arrayOutput);
        arrayScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        arrayScroll.set_hexpand(true);
        arrayScroll.set_vexpand(true);
        
        arrayTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK, 5);
        arrayTopBox.pack_start(arrayValueEntry, Gtk::PACK_SHRINK, 5);
        arrayTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK, 5);
        arrayTopBox.pack_start(arrayIndexEntry, Gtk::PACK_SHRINK, 5);
        
        arrayBottomBox.pack_start(arrayAppendButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arrayPrependButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arrayInsertButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arrayGetButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arrayConcatButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arraySubseqButton, Gtk::PACK_SHRINK, 5);
        arrayBottomBox.pack_start(arrayClearButton, Gtk::PACK_SHRINK, 5);
        
        arrayPage.pack_start(arrayTopBox, Gtk::PACK_SHRINK, 5);
        arrayPage.pack_start(arrayScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        arrayPage.pack_start(arrayBottomBox, Gtk::PACK_SHRINK, 5);
        
        notebook.append_page(arrayPage, "ArraySequence");
        
        listBuffer = Gtk::TextBuffer::create();
        listOutput.set_buffer(listBuffer);
        listOutput.set_editable(false);
        listScroll.add(listOutput);
        listScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        listScroll.set_hexpand(true);
        listScroll.set_vexpand(true);
        
        listTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK, 5);
        listTopBox.pack_start(listValueEntry, Gtk::PACK_SHRINK, 5);
        listTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK, 5);
        listTopBox.pack_start(listIndexEntry, Gtk::PACK_SHRINK, 5);
        
        listBottomBox.pack_start(listAppendButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listPrependButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listInsertButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listGetButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listConcatButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listSubseqButton, Gtk::PACK_SHRINK, 5);
        listBottomBox.pack_start(listClearButton, Gtk::PACK_SHRINK, 5);
        
        listPage.pack_start(listTopBox, Gtk::PACK_SHRINK, 5);
        listPage.pack_start(listScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        listPage.pack_start(listBottomBox, Gtk::PACK_SHRINK, 5);
        
        notebook.append_page(listPage, "ListSequence");
        
        mutableBuffer = Gtk::TextBuffer::create();
        mutableOutput.set_buffer(mutableBuffer);
        mutableOutput.set_editable(false);
        mutableScroll.add(mutableOutput);
        mutableScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        mutableScroll.set_hexpand(true);
        mutableScroll.set_vexpand(true);
        
        mutableTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK, 5);
        mutableTopBox.pack_start(mutableValueEntry, Gtk::PACK_SHRINK, 5);
        
        mutableBottomBox.pack_start(mutableAppendButton, Gtk::PACK_SHRINK, 5);
        mutableBottomBox.pack_start(mutablePrependButton, Gtk::PACK_SHRINK, 5);
        mutableBottomBox.pack_start(mutableInsertButton, Gtk::PACK_SHRINK, 5);
        
        mutablePage.pack_start(mutableTopBox, Gtk::PACK_SHRINK, 5);
        mutablePage.pack_start(mutableScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        mutablePage.pack_start(mutableBottomBox, Gtk::PACK_SHRINK, 5);
        
        notebook.append_page(mutablePage, "MutableArraySequence");
        
        immutableBuffer = Gtk::TextBuffer::create();
        immutableOutput.set_buffer(immutableBuffer);
        immutableOutput.set_editable(false);
        immutableScroll.add(immutableOutput);
        immutableScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        immutableScroll.set_hexpand(true);
        immutableScroll.set_vexpand(true);
        
        immutableTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK, 5);
        immutableTopBox.pack_start(immutableValueEntry, Gtk::PACK_SHRINK, 5);
        immutableTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK, 5);
        immutableTopBox.pack_start(immutableIndexEntry, Gtk::PACK_SHRINK, 5);
        
        immutableBottomBox.pack_start(immutableAppendButton, Gtk::PACK_SHRINK, 5);
        immutableBottomBox.pack_start(immutablePrependButton, Gtk::PACK_SHRINK, 5);
        immutableBottomBox.pack_start(immutableInsertButton, Gtk::PACK_SHRINK, 5);
        
        immutablePage.pack_start(immutableTopBox, Gtk::PACK_SHRINK, 5);
        immutablePage.pack_start(immutableScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        immutablePage.pack_start(immutableBottomBox, Gtk::PACK_SHRINK, 5);
        
        notebook.append_page(immutablePage, "ImmutableArraySequence");
        
        bitBuffer = Gtk::TextBuffer::create();
        bitOutput.set_buffer(bitBuffer);
        bitOutput.set_editable(false);
        bitScroll.add(bitOutput);
        bitScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        bitScroll.set_hexpand(true);
        bitScroll.set_vexpand(true);
        
        bitTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK, 5);
        bitTopBox.pack_start(bitIndexEntry, Gtk::PACK_SHRINK, 5);
        bitTopBox.pack_start(*makeLabel("Бит (0/1):"), Gtk::PACK_SHRINK, 5);
        bitTopBox.pack_start(bitValueEntry, Gtk::PACK_SHRINK, 5);
        bitTopBox.pack_start(*makeLabel("Размер:"), Gtk::PACK_SHRINK, 5);
        bitTopBox.pack_start(bitSizeEntry, Gtk::PACK_SHRINK, 5);
        
        bitBottomBox.pack_start(bitSetButton, Gtk::PACK_SHRINK, 5);
        bitBottomBox.pack_start(bitAndButton, Gtk::PACK_SHRINK, 5);
        bitBottomBox.pack_start(bitOrButton, Gtk::PACK_SHRINK, 5);
        bitBottomBox.pack_start(bitXorButton, Gtk::PACK_SHRINK, 5);
        bitBottomBox.pack_start(bitNotButton, Gtk::PACK_SHRINK, 5);
        
        bitPage.pack_start(bitTopBox, Gtk::PACK_SHRINK, 5);
        bitPage.pack_start(bitScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        bitPage.pack_start(bitBottomBox, Gtk::PACK_SHRINK, 5);
        
        notebook.append_page(bitPage, "BitSequence");
        
        funcBuffer = Gtk::TextBuffer::create();
        funcOutput.set_buffer(funcBuffer);
        funcOutput.set_editable(false);
        funcScroll.add(funcOutput);
        funcScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        funcScroll.set_hexpand(true);
        funcScroll.set_vexpand(true);
        
        seq1Box.pack_start(*makeLabel("Seq1:"), Gtk::PACK_SHRINK, 5);
        seq1Box.pack_start(seq1Entry, Gtk::PACK_EXPAND_WIDGET, 5);
        seq1Box.pack_start(seq1AddButton, Gtk::PACK_SHRINK, 5);
        seq1Box.pack_start(seq1ClearButton, Gtk::PACK_SHRINK, 5);
        
        seq2Box.pack_start(*makeLabel("Seq2:"), Gtk::PACK_SHRINK, 5);
        seq2Box.pack_start(seq2Entry, Gtk::PACK_EXPAND_WIDGET, 5);
        seq2Box.pack_start(seq2AddButton, Gtk::PACK_SHRINK, 5);
        seq2Box.pack_start(seq2ClearButton, Gtk::PACK_SHRINK, 5);
        
        funcButtonsBox.pack_start(mapButton, Gtk::PACK_SHRINK, 5);
        funcButtonsBox.pack_start(whereButton, Gtk::PACK_SHRINK, 5);
        funcButtonsBox.pack_start(reduceButton, Gtk::PACK_SHRINK, 5);
        funcButtonsBox.pack_start(zipButton, Gtk::PACK_SHRINK, 5);
        
        funcBox.pack_start(seq1Box, Gtk::PACK_SHRINK, 5);
        funcBox.pack_start(seq2Box, Gtk::PACK_SHRINK, 5);
        funcBox.pack_start(funcButtonsBox, Gtk::PACK_SHRINK, 5);
        funcBox.pack_start(funcScroll, Gtk::PACK_EXPAND_WIDGET, 5);
        
        funcPage.pack_start(funcBox, Gtk::PACK_EXPAND_WIDGET, 5);
        notebook.append_page(funcPage, "Map/Reduce");
        
        arrayAppendButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayAppend));
        arrayPrependButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayPrepend));
        arrayInsertButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayInsert));
        arrayGetButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayGet));
        arrayConcatButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayConcat));
        arraySubseqButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArraySubseq));
        arrayClearButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onArrayClear));
        
        listAppendButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListAppend));
        listPrependButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListPrepend));
        listInsertButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListInsert));
        listGetButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListGet));
        listConcatButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListConcat));
        listSubseqButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListSubseq));
        listClearButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onListClear));
        
        mutableAppendButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onMutableAppend));
        mutablePrependButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onMutablePrepend));
        mutableInsertButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onMutableInsert));
        
        immutableAppendButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onImmutableAppend));
        immutablePrependButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onImmutablePrepend));
        immutableInsertButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onImmutableInsert));
        
        bitSetButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onBitSet));
        bitAndButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onBitAnd));
        bitOrButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onBitOr));
        bitXorButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onBitXor));
        bitNotButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onBitNot));
        
        mapButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onMap));
        whereButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onWhere));
        reduceButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onReduce));
        zipButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onZip));
        
        seq1AddButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSeq1Add));
        seq1ClearButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSeq1Clear));
        seq2AddButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSeq2Add));
        seq2ClearButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onSeq2Clear));
        
        show_all_children();
        
        appendArrayOutput("Программа запущена");
        appendListOutput("Программа запущена");
        appendMutableOutput("Программа запущена");
        appendImmutableOutput("Программа запущена");
        appendBitOutput("Программа запущена");
        appendFuncOutput("Программа запущена");
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.lab2.app");
    MainWindow window;
    return app->run(window);
}