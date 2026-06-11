#include <gtkmm.h>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include "Functional.hpp"
#include "SquareMatrix.hpp"
#include "Exception.hpp"

class MainWindow : public Gtk::Window {
private:
    Sequence<int>* arraySeq;
    Sequence<int>* listSeq;
    Sequence<int>* mutableSeq;
    Sequence<int>* immutableSeq;
    Sequence<bool>* bitSeq1;
    Sequence<int>* seq1;
    Sequence<int>* seq2;

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
    Gtk::Button splitButton;
    Gtk::Button seq1AddButton;
    Gtk::Button seq1ClearButton;
    Gtk::Button seq2AddButton;
    Gtk::Button seq2ClearButton;
    Gtk::Button iteratorsButton;
    Gtk::Button unzipButton;

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

    Gtk::Box squareMatrixPage;
    Gtk::Box squareMatrixTopBox;
    Gtk::Box squareMatrixBottomBox;
    Gtk::Entry matrixSizeEntry;
    Gtk::Button matrixCreateButton;
    Gtk::Grid matrixInputGrid;
    DynamicArray<DynamicArray<Gtk::Entry*>> matrixEntries;
    SquareMatrix<double> currentMatrix;
    Gtk::Button matrixAddButton;
    Gtk::Button matrixScalarButton;
    Gtk::Button matrixNormButton;
    Gtk::Button matrixSwapRowsButton;
    Gtk::Button matrixMultiplyRowButton;
    Gtk::Button matrixAddRowButton;
    Gtk::Button matrixSwapColsButton;
    Gtk::Button matrixMultiplyColButton;
    Gtk::Button matrixAddColButton;
    Gtk::Button matrixMultiplyButton;
    Gtk::ScrolledWindow squareMatrixScroll;
    Gtk::TextView squareMatrixOutput;
    Glib::RefPtr<Gtk::TextBuffer> squareMatrixBuffer;
    Gtk::Entry scalarEntry;
    Gtk::Entry rowIndexEntry;
    Gtk::Entry factorEntry;
    Gtk::Entry targetEntry;
    Gtk::Entry sourceEntry;
    Gtk::Entry matrixInitEntry;
    Gtk::Button matrixInitButton;

    template<typename T>
    std::string toString(const T& value) { return std::to_string(value); }
    std::string toString(const char* value) { return std::string(value); }
    std::string toString(const std::string& value) { return value; }

    void appendPart(const Glib::ustring& text) { squareMatrixBuffer->insert(squareMatrixBuffer->end(), text); }
    template<typename First, typename... Rest> void appendParts(First first, Rest... rest) {
        appendPart(Glib::ustring(toString(first)));
        appendParts(rest...);
    }
    void appendParts() { appendPart(Glib::ustring("\n")); }

    void appendArrayOutput(const Glib::ustring& text) { arrayBuffer->insert(arrayBuffer->end(), text + "\n"); }
    void appendListOutput(const Glib::ustring& text) { listBuffer->insert(listBuffer->end(), text + "\n"); }
    void appendMutableOutput(const Glib::ustring& text) { mutableBuffer->insert(mutableBuffer->end(), text + "\n"); }
    void appendImmutableOutput(const Glib::ustring& text) { immutableBuffer->insert(immutableBuffer->end(), text + "\n"); }
    void appendBitOutput(const Glib::ustring& text) { bitBuffer->insert(bitBuffer->end(), text + "\n"); }
    void appendFuncOutput(const Glib::ustring& text) { funcBuffer->insert(funcBuffer->end(), text + "\n"); }
    void appendMatrixOutputLine(const Glib::ustring& text) { squareMatrixBuffer->insert(squareMatrixBuffer->end(), text + "\n"); }

    template<typename... Args> void appendArrayOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendArrayOutput(Glib::ustring(ss.str()));
    }
    template<typename... Args> void appendListOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendListOutput(Glib::ustring(ss.str()));
    }
    template<typename... Args> void appendMutableOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendMutableOutput(Glib::ustring(ss.str()));
    }
    template<typename... Args> void appendImmutableOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendImmutableOutput(Glib::ustring(ss.str()));
    }
    template<typename... Args> void appendBitOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendBitOutput(Glib::ustring(ss.str()));
    }
    template<typename... Args> void appendFuncOutputParts(Args... args) {
        std::stringstream ss; (ss << ... << args); appendFuncOutput(Glib::ustring(ss.str()));
    }

    Glib::ustring getSequenceString(Sequence<int>* seq) {
        std::stringstream ss; ss << "[";
        for (int i = 0; i < seq->GetLength(); ++i) {
            ss << seq->Get(i); if (i < seq->GetLength() - 1) ss << ", ";
        }
        ss << "]"; return Glib::ustring(ss.str());
    }
    Glib::ustring getBitString(Sequence<bool>* seq) {
        std::stringstream ss;
        for (int i = 0; i < seq->GetLength(); ++i) ss << (seq->Get(i) ? "1" : "0");
        return Glib::ustring(ss.str());
    }

    int safe_stoi(const Glib::ustring& str, const std::string& fieldName = "") {
        if (str.empty()) {
            std::stringstream ss;
            ss << "Поле " << fieldName << " пустое";
            throw InvalidArgumentError(ss.str());
        }
        try { return std::stoi(str); }
        catch (const std::invalid_argument&) {
            std::stringstream ss;
            ss << "Поле " << fieldName << " содержит не число: " << str;
            throw InvalidArgumentError(ss.str());
        }
        catch (const std::out_of_range&) {
            std::stringstream ss;
            ss << "Число в поле " << fieldName << " вне допустимого диапазона";
            throw InvalidArgumentError(ss.str());
        }
    }

    double safe_stod(const Glib::ustring& str, const std::string& fieldName = "") {
        if (str.empty()) {
            std::stringstream ss;
            ss << "Поле " << fieldName << " пустое";
            throw InvalidArgumentError(ss.str());
        }
        try { return std::stod(str); }
        catch (const std::invalid_argument&) {
            std::stringstream ss;
            ss << "Поле " << fieldName << " содержит не число: " << str;
            throw InvalidArgumentError(ss.str());
        }
        catch (const std::out_of_range&) {
            std::stringstream ss;
            ss << "Число в поле " << fieldName << " вне допустимого диапазона";
            throw InvalidArgumentError(ss.str());
        }
    }

    void onArrayAppend() {
        try {
            int value = safe_stoi(arrayValueEntry.get_text(), "значение");
            arraySeq->Append(value);
            appendArrayOutputParts("Добавить ", value, ": ", getSequenceString(arraySeq));
            arrayValueEntry.set_text("");
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArrayPrepend() {
        try {
            int value = safe_stoi(arrayValueEntry.get_text(), "значение");
            arraySeq->Prepend(value);
            appendArrayOutputParts("Добавить в начало ", value, ": ", getSequenceString(arraySeq));
            arrayValueEntry.set_text("");
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArrayInsert() {
        try {
            int idx = safe_stoi(arrayIndexEntry.get_text(), "индекс");
            int val = safe_stoi(arrayValueEntry.get_text(), "значение");
            arraySeq->InsertAt(val, idx);
            appendArrayOutputParts("Вставить ", val, " в ", idx, ": ", getSequenceString(arraySeq));
            arrayIndexEntry.set_text(""); arrayValueEntry.set_text("");
        } catch (const IndexOutOfRange& e) {
            if (e.HasDetails()) appendArrayOutputParts("Ошибка: индекс ", e.GetIndex(), " вне диапазона [0, ", e.GetSize()-1, "]");
            else appendArrayOutput(e.what());
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArrayGet() {
        try {
            int idx = safe_stoi(arrayIndexEntry.get_text(), "индекс");
            int val = arraySeq->Get(idx);
            appendArrayOutputParts("Получить[", idx, "] = ", val);
            arrayIndexEntry.set_text("");
        } catch (const IndexOutOfRange& e) {
            if (e.HasDetails()) appendArrayOutputParts("Ошибка: индекс ", e.GetIndex(), " вне диапазона [0, ", e.GetSize()-1, "]");
            else appendArrayOutput(e.what());
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArrayConcat() {
        try {
            MutableArraySequence<int> tmp; tmp.Append(100); tmp.Append(200); tmp.Append(300);
            Sequence<int>* res = arraySeq->Concat(tmp);
            appendArrayOutputParts("Склеить с [100,200,300]: ", getSequenceString(res));
            delete res;
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArraySubseq() {
        try {
            int start = safe_stoi(arrayIndexEntry.get_text(), "начальный индекс");
            Sequence<int>* sub = arraySeq->GetSubsequence(start, arraySeq->GetLength()-1);
            appendArrayOutputParts("Подпоследовательность с ", start, ": ", getSequenceString(sub));
            delete sub; arrayIndexEntry.set_text("");
        } catch (const std::exception& e) { appendArrayOutput(e.what()); }
    }
    void onArrayClear() { try { arraySeq->Clear(); appendArrayOutputParts("Очистить: ", getSequenceString(arraySeq)); } catch (const std::exception& e) { appendArrayOutput(e.what()); } }

    void onListAppend() {
        try {
            int v = safe_stoi(listValueEntry.get_text(), "значение");
            listSeq->Append(v);
            appendListOutputParts("Добавить ", v, ": ", getSequenceString(listSeq));
            listValueEntry.set_text("");
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListPrepend() {
        try {
            int v = safe_stoi(listValueEntry.get_text(), "значение");
            listSeq->Prepend(v);
            appendListOutputParts("Добавить в начало ", v, ": ", getSequenceString(listSeq));
            listValueEntry.set_text("");
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListInsert() {
        try {
            int idx = safe_stoi(listIndexEntry.get_text(), "индекс");
            int val = safe_stoi(listValueEntry.get_text(), "значение");
            listSeq->InsertAt(val, idx);
            appendListOutputParts("Вставить ", val, " в ", idx, ": ", getSequenceString(listSeq));
            listIndexEntry.set_text(""); listValueEntry.set_text("");
        } catch (const IndexOutOfRange& e) {
            if (e.HasDetails()) appendListOutputParts("Ошибка: индекс ", e.GetIndex(), " вне диапазона [0, ", e.GetSize()-1, "]");
            else appendListOutput(e.what());
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListGet() {
        try {
            int idx = safe_stoi(listIndexEntry.get_text(), "индекс");
            int val = listSeq->Get(idx);
            appendListOutputParts("Получить[", idx, "] = ", val);
            listIndexEntry.set_text("");
        } catch (const IndexOutOfRange& e) {
            if (e.HasDetails()) appendListOutputParts("Ошибка: индекс ", e.GetIndex(), " вне диапазона [0, ", e.GetSize()-1, "]");
            else appendListOutput(e.what());
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListConcat() {
        try {
            ListSequence<int> tmp; tmp.Append(100); tmp.Append(200); tmp.Append(300);
            Sequence<int>* res = listSeq->Concat(tmp);
            appendListOutputParts("Склеить с [100,200,300]: ", getSequenceString(res));
            delete res;
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListSubseq() {
        try {
            int start = safe_stoi(listIndexEntry.get_text(), "начальный индекс");
            Sequence<int>* sub = listSeq->GetSubsequence(start, listSeq->GetLength()-1);
            appendListOutputParts("Подпоследовательность с ", start, ": ", getSequenceString(sub));
            delete sub; listIndexEntry.set_text("");
        } catch (const std::exception& e) { appendListOutput(e.what()); }
    }
    void onListClear() { try { listSeq->Clear(); appendListOutputParts("Очистить: ", getSequenceString(listSeq)); } catch (const std::exception& e) { appendListOutput(e.what()); } }

    void onMutableAppend() {
        try {
            int v = safe_stoi(mutableValueEntry.get_text(), "значение");
            mutableSeq->Append(v);
            appendMutableOutputParts("Mutable Добавить ", v, ": ", getSequenceString(mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendMutableOutput(e.what()); }
    }
    void onMutablePrepend() {
        try {
            int v = safe_stoi(mutableValueEntry.get_text(), "значение");
            mutableSeq->Prepend(v);
            appendMutableOutputParts("Mutable Добавить в начало ", v, ": ", getSequenceString(mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendMutableOutput(e.what()); }
    }
    void onMutableInsert() {
        try {
            int idx = safe_stoi(mutableValueEntry.get_text(), "индекс");
            int val = safe_stoi(mutableValueEntry.get_text(), "значение");
            mutableSeq->InsertAt(val, idx);
            appendMutableOutputParts("Mutable Вставить ", val, " в ", idx, ": ", getSequenceString(mutableSeq));
            mutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendMutableOutput(e.what()); }
    }

    void onImmutableAppend() {
        try {
            int v = safe_stoi(immutableValueEntry.get_text(), "значение");
            ImmutableArraySequence<int>* newSeq = static_cast<ImmutableArraySequence<int>*>(immutableSeq)->AppendImmutable(v);
            appendImmutableOutputParts("Immutable Добавить ", v);
            appendImmutableOutputParts("  Было: ", getSequenceString(immutableSeq));
            appendImmutableOutputParts("  Стало: ", getSequenceString(newSeq));
            delete immutableSeq; immutableSeq = newSeq;
            immutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendImmutableOutput(e.what()); }
    }
    void onImmutablePrepend() {
        try {
            int v = safe_stoi(immutableValueEntry.get_text(), "значение");
            ImmutableArraySequence<int>* newSeq = static_cast<ImmutableArraySequence<int>*>(immutableSeq)->PrependImmutable(v);
            appendImmutableOutputParts("Immutable Добавить в начало ", v);
            appendImmutableOutputParts("  Было: ", getSequenceString(immutableSeq));
            appendImmutableOutputParts("  Стало: ", getSequenceString(newSeq));
            delete immutableSeq; immutableSeq = newSeq;
            immutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendImmutableOutput(e.what()); }
    }
    void onImmutableInsert() {
        try {
            int idx = safe_stoi(immutableIndexEntry.get_text(), "индекс");
            int val = safe_stoi(immutableValueEntry.get_text(), "значение");
            ImmutableArraySequence<int>* newSeq = static_cast<ImmutableArraySequence<int>*>(immutableSeq)->InsertAtImmutable(val, idx);
            appendImmutableOutputParts("Immutable Вставить ", val, " в ", idx);
            appendImmutableOutputParts("  Было: ", getSequenceString(immutableSeq));
            appendImmutableOutputParts("  Стало: ", getSequenceString(newSeq));
            delete immutableSeq; immutableSeq = newSeq;
            immutableIndexEntry.set_text(""); immutableValueEntry.set_text("");
        } catch (const std::exception& e) { appendImmutableOutput(e.what()); }
    }

    void onBitSet() {
        try {
            int idx = safe_stoi(bitIndexEntry.get_text(), "индекс");
            int val = safe_stoi(bitValueEntry.get_text(), "бит");
            if (bitSeq1->GetLength() <= idx) {
                BitSequence* ns = new BitSequence(idx+1);
                for (int i=0; i<bitSeq1->GetLength(); ++i) ns->Set(i, bitSeq1->Get(i));
                delete bitSeq1; bitSeq1 = ns;
            }
            static_cast<BitSequence*>(bitSeq1)->Set(idx, val==1);
            appendBitOutputParts("BitSequence1: ", getBitString(bitSeq1));
            bitIndexEntry.set_text(""); bitValueEntry.set_text("");
        } catch (const std::exception& e) { appendBitOutput(e.what()); }
    }
    void onBitAnd() {
        try {
            int sz = safe_stoi(bitSizeEntry.get_text(), "размер");
            BitSequence seq2(sz);
            for (int i=0; i<sz && i<bitSeq1->GetLength(); ++i) seq2.Set(i, bitSeq1->Get(i));
            BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) & seq2;
            appendBitOutputParts("BitSequence1 И BitSequence2: ", getBitString(&res));
        } catch (const std::exception& e) { appendBitOutput(e.what()); }
    }
    void onBitOr() {
        try {
            int sz = safe_stoi(bitSizeEntry.get_text(), "размер");
            BitSequence seq2(sz);
            for (int i=0; i<sz && i<bitSeq1->GetLength(); ++i) seq2.Set(i, bitSeq1->Get(i));
            BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) | seq2;
            appendBitOutputParts("BitSequence1 ИЛИ BitSequence2: ", getBitString(&res));
        } catch (const std::exception& e) { appendBitOutput(e.what()); }
    }
    void onBitXor() {
        try {
            int sz = safe_stoi(bitSizeEntry.get_text(), "размер");
            BitSequence seq2(sz);
            for (int i=0; i<sz && i<bitSeq1->GetLength(); ++i) seq2.Set(i, bitSeq1->Get(i));
            BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) ^ seq2;
            appendBitOutputParts("BitSequence1 ИСКЛЮЧАЮЩЕЕ ИЛИ BitSequence2: ", getBitString(&res));
        } catch (const std::exception& e) { appendBitOutput(e.what()); }
    }
    void onBitNot() {
        try {
            BitSequence res = ~(*static_cast<BitSequence*>(bitSeq1));
            appendBitOutputParts("НЕ BitSequence1: ", getBitString(&res));
        } catch (const std::exception& e) { appendBitOutput(e.what()); }
    }

    void onMap() {
        try {
            if (seq1->GetLength()==0) { appendFuncOutput("Ошибка: первая последовательность пуста"); return; }
            Sequence<int>* res = Functional<int,int>::Map(seq1, [](int x){return x*x;});
            appendFuncOutputParts("Map ", getSequenceString(seq1), " -> квадраты: ", getSequenceString(res));
            delete res;
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onWhere() {
        try {
            if (seq1->GetLength()==0) { appendFuncOutput("Ошибка: первая последовательность пуста"); return; }
            Sequence<int>* res = Functional<int,int>::Where(seq1, [](int x){return x%2==0;});
            appendFuncOutputParts("Where ", getSequenceString(seq1), " -> четные: ", getSequenceString(res));
            delete res;
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onReduce() {
        try {
            if (seq1->GetLength()==0) { appendFuncOutput("Ошибка: первая последовательность пуста"); return; }
            int sum = Functional<int,int>::Reduce(seq1, [](int a,int b){return a+b;},0);
            int prod = Functional<int,int>::Reduce(seq1, [](int a,int b){return a*b;},1);
            appendFuncOutputParts("Reduce ", getSequenceString(seq1), " -> сумма = ", sum, ", произведение = ", prod);
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onZip() {
        try {
            if (seq1->GetLength()==0 || seq2->GetLength()==0) { appendFuncOutput("Ошибка: пустые последовательности"); return; }
            Sequence<std::pair<int,int>>* z = Functional<int,int>::Zip(seq1, seq2);
            std::stringstream ss; ss << "[";
            for (int i=0; i<z->GetLength(); ++i) ss << "(" << z->Get(i).first << "," << z->Get(i).second << ")";
            ss << "]";
            appendFuncOutputParts("Zip ", getSequenceString(seq1), " и ", getSequenceString(seq2), " -> ", ss.str());
            delete z;
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onSplit() {
        try {
            if (seq1->GetLength()==0) { appendFuncOutput("Ошибка: Seq1 пуста"); return; }
            Sequence<Sequence<int>*>* res = Functional<int,int>::Split(seq1, [](int x){return x==0;});
            std::stringstream ss; ss << "Split по нулю: ";
            for (int i=0; i<res->GetLength(); ++i) ss << getSequenceString(res->Get(i)) << ", ";
            appendFuncOutput(ss.str());
            for (int i=0; i<res->GetLength(); ++i) delete res->Get(i);
            delete res;
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onSeq1Add() {
        try {
            std::string inp = seq1Entry.get_text();
            std::stringstream ss(inp); int num; DynamicArray<int> vals; bool tooBig=false;
            while (ss>>num) { if (num>40000||num<-40000) { tooBig=true; break; } vals.Append(num); }
            if (tooBig) { appendFuncOutput("Ошибка: числа >40000 или <-40000 не допускаются"); seq1Entry.set_text(""); return; }
            for (size_t i=0; i<vals.GetSize(); ++i) seq1->Append(vals.Get(i));
            appendFuncOutputParts("Seq1 добавлены: ", getSequenceString(seq1));
            seq1Entry.set_text("");
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onSeq1Clear() { try { seq1->Clear(); appendFuncOutputParts("Seq1 очищена"); } catch (const std::exception& e) { appendFuncOutput(e.what()); } }
    void onSeq2Add() {
        try {
            std::string inp = seq2Entry.get_text();
            std::stringstream ss(inp); int num; DynamicArray<int> vals; bool tooBig=false;
            while (ss>>num) { if (num>40000||num<-40000) { tooBig=true; break; } vals.Append(num); }
            if (tooBig) { appendFuncOutput("Ошибка: числа >40000 или <-40000 не допускаются"); seq2Entry.set_text(""); return; }
            for (size_t i=0; i<vals.GetSize(); ++i) seq2->Append(vals.Get(i));
            appendFuncOutputParts("Seq2 добавлены: ", getSequenceString(seq2));
            seq2Entry.set_text("");
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onSeq2Clear() { try { seq2->Clear(); appendFuncOutputParts("Seq2 очищена"); } catch (const std::exception& e) { appendFuncOutput(e.what()); } }

    void onDemoIterators() {
        try {
            if (seq1->GetLength()==0) { appendFuncOutput("Ошибка: Seq1 пуста"); return; }
            std::stringstream ss; ss << "Итератор по Seq1: [";
            for (int x : *static_cast<ArraySequence<int>*>(seq1)) ss << x << " ";
            ss << "]"; appendFuncOutput(ss.str());
            for (auto& x : *static_cast<ArraySequence<int>*>(seq1)) x *= 2;
            ss.str(""); ss << "После умножения на 2: [";
            for (int x : *static_cast<ArraySequence<int>*>(seq1)) ss << x << " ";
            ss << "]"; appendFuncOutput(ss.str());
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }
    void onUnzip() {
        try {
            if (seq1->GetLength()==0||seq2->GetLength()==0) { appendFuncOutput("Ошибка: пустые"); return; }
            Sequence<std::pair<int,int>>* z = Functional<int,int>::Zip(seq1, seq2);
            auto u = Functional<int,int>::Unzip(z);
            appendFuncOutputParts("Unzip: ", getSequenceString(u.first), " и ", getSequenceString(u.second));
            delete z; delete u.first; delete u.second;
        } catch (const std::exception& e) { appendFuncOutput(e.what()); }
    }

    void rebuildMatrixInputGrid() {
        for (size_t i=0; i<matrixEntries.GetSize(); ++i)
            for (size_t j=0; j<matrixEntries.Get(i).GetSize(); ++j) delete matrixEntries.Get(i).Get(j);
        matrixEntries.Clear();
        std::vector<Gtk::Widget*> ch = matrixInputGrid.get_children();
        for (auto c : ch) matrixInputGrid.remove(*c);
        int n = currentMatrix.GetSize();
        for (int i=0; i<n; ++i) {
            DynamicArray<Gtk::Entry*> row;
            for (int j=0; j<n; ++j) {
                Gtk::Entry* e = new Gtk::Entry();
                e->set_text(std::to_string(currentMatrix.Get(i,j)));
                e->set_hexpand(true);
                row.Append(e);
                matrixInputGrid.attach(*e, j, i, 1,1);
            }
            matrixEntries.Append(row);
        }
        matrixInputGrid.show_all();
    }
    void printMatrix(const SquareMatrix<double>& m) {
        int n = m.GetSize();
        for (int i=0; i<n; ++i) {
            std::stringstream ss; ss << "[";
            for (int j=0; j<n; ++j) { ss << m.Get(i,j); if (j<n-1) ss << ", "; }
            ss << "]";
            appendMatrixOutputLine(Glib::ustring(ss.str()));
        }
    }

    void onMatrixCreate() {
        try {
            int n = safe_stoi(matrixSizeEntry.get_text(), "размер матрицы");
            if (n <= 0) throw InvalidArgumentError("Размер матрицы должен быть положительным");
            currentMatrix = SquareMatrix<double>(n);
            rebuildMatrixInputGrid();
            appendParts("Создана матрица ", n, "x", n);
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixInit() {
        try {
            int n = currentMatrix.GetSize();
            if (n==0) { appendMatrixOutputLine("Сначала создайте матрицу"); return; }
            std::string inp = matrixInitEntry.get_text();
            std::stringstream ss(inp); DynamicArray<double> vals; double v;
            while (ss>>v) vals.Append(v);
            if (vals.GetSize() != (size_t)(n*n)) { appendParts("Ошибка: нужно ", n*n, " чисел"); return; }
            for (int i=0; i<n; ++i)
                for (int j=0; j<n; ++j)
                    currentMatrix.Set(i,j, vals.Get(i*n+j));
            rebuildMatrixInputGrid();
            appendMatrixOutputLine("Значения матрицы обновлены");
            printMatrix(currentMatrix);
            matrixInitEntry.set_text("");
        } catch (const IndexOutOfRange& e) {
            if (e.HasDetails()) appendParts("Ошибка: индекс ", e.GetIndex(), " вне диапазона [0, ", e.GetSize()-1, "]");
            else appendMatrixOutputLine(e.what());
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixAdd() {
        try {
            int n = currentMatrix.GetSize();
            SquareMatrix<double> other(n);
            for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
                std::stringstream ss; ss << "ячейка[" << i << "][" << j << "]";
                double val = safe_stod(matrixEntries.Get(i).Get(j)->get_text(), ss.str()); 
                other.Set(i,j, val);
            }
            SquareMatrix<double> res = currentMatrix.Add(other);
            appendMatrixOutputLine("Результат сложения:"); printMatrix(res);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixScalar() {
        try {
            double s = safe_stod(scalarEntry.get_text(), "скаляр");
            SquareMatrix<double> res = currentMatrix.MultiplyByScalar(s);
            appendParts("Результат умножения на ", s, ":"); printMatrix(res);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixNorm() {
        try { appendParts("Норма матрицы: ", currentMatrix.Norm()); }
        catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixSwapRows() {
        try {
            int i = safe_stoi(rowIndexEntry.get_text(), "первая строка");
            int j = safe_stoi(targetEntry.get_text(), "вторая строка");
            currentMatrix.SwapRows(i,j);
            rebuildMatrixInputGrid();
            appendParts("Строки ", i, " и ", j, " поменяны местами");
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixMultiplyRow() {
        try {
            int i = safe_stoi(rowIndexEntry.get_text(), "индекс строки");
            double f = safe_stod(factorEntry.get_text(), "множитель");
            currentMatrix.MultiplyRow(i,f);
            rebuildMatrixInputGrid();
            appendParts("Строка ", i, " умножена на ", f);
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixAddRow() {
        try {
            int t = safe_stoi(targetEntry.get_text(), "строка-получатель");
            int s = safe_stoi(sourceEntry.get_text(), "строка-источник");
            double f = safe_stod(factorEntry.get_text(), "множитель");
            currentMatrix.AddRow(t,s,f);
            rebuildMatrixInputGrid();
            appendParts("К строке ", t, " прибавлена строка ", s, " * ", f);
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixSwapCols() {
        try {
            int i = safe_stoi(rowIndexEntry.get_text(), "первый столбец");
            int j = safe_stoi(targetEntry.get_text(), "второй столбец");
            currentMatrix.SwapCols(i,j);
            rebuildMatrixInputGrid();
            appendParts("Столбцы ", i, " и ", j, " поменяны местами");
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixMultiplyCol() {
        try {
            int j = safe_stoi(rowIndexEntry.get_text(), "индекс столбца");
            double f = safe_stod(factorEntry.get_text(), "множитель");
            currentMatrix.MultiplyCol(j,f);
            rebuildMatrixInputGrid();
            appendParts("Столбец ", j, " умножен на ", f);
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixAddCol() {
        try {
            int t = safe_stoi(targetEntry.get_text(), "столбец-получатель");
            int s = safe_stoi(sourceEntry.get_text(), "столбец-источник");
            double f = safe_stod(factorEntry.get_text(), "множитель");
            currentMatrix.AddCol(t,s,f);
            rebuildMatrixInputGrid();
            appendParts("К столбцу ", t, " прибавлен столбец ", s, " * ", f);
            printMatrix(currentMatrix);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }
    void onMatrixMultiply() {
        try {
            int n = currentMatrix.GetSize();
            SquareMatrix<double> other(n);
            for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
                double val = safe_stod(matrixEntries.Get(i).Get(j)->get_text(), "ячейка["+std::to_string(i)+"]["+std::to_string(j)+"]");
                other.Set(i,j, val);
            }
            SquareMatrix<double> res = currentMatrix.Multiply(other);
            appendMatrixOutputLine("Результат умножения матриц:"); printMatrix(res);
        } catch (const std::exception& e) { appendMatrixOutputLine(e.what()); }
    }

    Gtk::Label* makeLabel(const Glib::ustring& t) { return Gtk::make_managed<Gtk::Label>(t); }

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
        splitButton("Split по нулю"),
        seq1AddButton("Добавить в Seq1"),
        seq1ClearButton("Очистить Seq1"),
        seq2AddButton("Добавить в Seq2"),
        seq2ClearButton("Очистить Seq2"),
        iteratorsButton("Тест итераторов"),
        unzipButton("Unzip"),
        arraySeq(new MutableArraySequence<int>()),
        listSeq(new ListSequence<int>()),
        mutableSeq(new MutableArraySequence<int>()),
        immutableSeq(new ImmutableArraySequence<int>(new int[5]{10,20,30,40,50}, 5)),
        bitSeq1(new BitSequence()),
        seq1(new ArraySequence<int>()),
        seq2(new ArraySequence<int>()),
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
        seq2Entry(),
        squareMatrixTopBox(Gtk::ORIENTATION_VERTICAL, 10),
        squareMatrixBottomBox(Gtk::ORIENTATION_VERTICAL, 10),
        matrixCreateButton("Создать матрицу"),
        matrixInitButton("Установить значения"),
        matrixAddButton("Сложение"),
        matrixScalarButton("Умножить на скаляр"),
        matrixNormButton("Норма"),
        matrixSwapRowsButton("Поменять строки"),
        matrixMultiplyRowButton("Умножить строку"),
        matrixAddRowButton("Прибавить строку"),
        matrixSwapColsButton("Поменять столбцы"),
        matrixMultiplyColButton("Умножить столбец"),
        matrixAddColButton("Прибавить столбец"),
        matrixMultiplyButton("Умножить матрицы"),
        matrixSizeEntry(),
        matrixInitEntry(),
        scalarEntry(),
        rowIndexEntry(),
        factorEntry(),
        targetEntry(),
        sourceEntry(),
        squareMatrixBuffer(Gtk::TextBuffer::create()),
        squareMatrixOutput(),
        squareMatrixScroll(),
        matrixInputGrid(),
        matrixEntries() {

        set_title("Лабораторная работа 2 и 3");
        set_default_size(1200,800);
        srand(time(nullptr));
        add(mainBox);
        notebook.set_hexpand(true); notebook.set_vexpand(true);
        mainBox.pack_start(notebook, Gtk::PACK_EXPAND_WIDGET, 5);

        
        arrayBuffer = Gtk::TextBuffer::create();
        arrayOutput.set_buffer(arrayBuffer); arrayOutput.set_editable(false);
        arrayScroll.add(arrayOutput);
        arrayScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        arrayScroll.set_hexpand(true); arrayScroll.set_vexpand(true);

        arrayTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK,5);
        arrayTopBox.pack_start(arrayValueEntry, Gtk::PACK_SHRINK,5);
        arrayTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK,5);
        arrayTopBox.pack_start(arrayIndexEntry, Gtk::PACK_SHRINK,5);

        arrayBottomBox.pack_start(arrayAppendButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arrayPrependButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arrayInsertButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arrayGetButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arrayConcatButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arraySubseqButton, Gtk::PACK_SHRINK,5);
        arrayBottomBox.pack_start(arrayClearButton, Gtk::PACK_SHRINK,5);

        arrayPage.pack_start(arrayTopBox, Gtk::PACK_SHRINK,5);
        arrayPage.pack_start(arrayScroll, Gtk::PACK_EXPAND_WIDGET,5);
        arrayPage.pack_start(arrayBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(arrayPage, "ArraySequence");

        
        listBuffer = Gtk::TextBuffer::create();
        listOutput.set_buffer(listBuffer); listOutput.set_editable(false);
        listScroll.add(listOutput);
        listScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        listScroll.set_hexpand(true); listScroll.set_vexpand(true);

        listTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK,5);
        listTopBox.pack_start(listValueEntry, Gtk::PACK_SHRINK,5);
        listTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK,5);
        listTopBox.pack_start(listIndexEntry, Gtk::PACK_SHRINK,5);

        listBottomBox.pack_start(listAppendButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listPrependButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listInsertButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listGetButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listConcatButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listSubseqButton, Gtk::PACK_SHRINK,5);
        listBottomBox.pack_start(listClearButton, Gtk::PACK_SHRINK,5);

        listPage.pack_start(listTopBox, Gtk::PACK_SHRINK,5);
        listPage.pack_start(listScroll, Gtk::PACK_EXPAND_WIDGET,5);
        listPage.pack_start(listBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(listPage, "ListSequence");

        
        mutableBuffer = Gtk::TextBuffer::create();
        mutableOutput.set_buffer(mutableBuffer); mutableOutput.set_editable(false);
        mutableScroll.add(mutableOutput);
        mutableScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        mutableScroll.set_hexpand(true); mutableScroll.set_vexpand(true);

        mutableTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK,5);
        mutableTopBox.pack_start(mutableValueEntry, Gtk::PACK_SHRINK,5);

        mutableBottomBox.pack_start(mutableAppendButton, Gtk::PACK_SHRINK,5);
        mutableBottomBox.pack_start(mutablePrependButton, Gtk::PACK_SHRINK,5);
        mutableBottomBox.pack_start(mutableInsertButton, Gtk::PACK_SHRINK,5);

        mutablePage.pack_start(mutableTopBox, Gtk::PACK_SHRINK,5);
        mutablePage.pack_start(mutableScroll, Gtk::PACK_EXPAND_WIDGET,5);
        mutablePage.pack_start(mutableBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(mutablePage, "MutableArraySequence");

        
        immutableBuffer = Gtk::TextBuffer::create();
        immutableOutput.set_buffer(immutableBuffer); immutableOutput.set_editable(false);
        immutableScroll.add(immutableOutput);
        immutableScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        immutableScroll.set_hexpand(true); immutableScroll.set_vexpand(true);

        immutableTopBox.pack_start(*makeLabel("Значение:"), Gtk::PACK_SHRINK,5);
        immutableTopBox.pack_start(immutableValueEntry, Gtk::PACK_SHRINK,5);
        immutableTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK,5);
        immutableTopBox.pack_start(immutableIndexEntry, Gtk::PACK_SHRINK,5);

        immutableBottomBox.pack_start(immutableAppendButton, Gtk::PACK_SHRINK,5);
        immutableBottomBox.pack_start(immutablePrependButton, Gtk::PACK_SHRINK,5);
        immutableBottomBox.pack_start(immutableInsertButton, Gtk::PACK_SHRINK,5);

        immutablePage.pack_start(immutableTopBox, Gtk::PACK_SHRINK,5);
        immutablePage.pack_start(immutableScroll, Gtk::PACK_EXPAND_WIDGET,5);
        immutablePage.pack_start(immutableBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(immutablePage, "ImmutableArraySequence");

        
        bitBuffer = Gtk::TextBuffer::create();
        bitOutput.set_buffer(bitBuffer); bitOutput.set_editable(false);
        bitScroll.add(bitOutput);
        bitScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        bitScroll.set_hexpand(true); bitScroll.set_vexpand(true);

        bitTopBox.pack_start(*makeLabel("Индекс:"), Gtk::PACK_SHRINK,5);
        bitTopBox.pack_start(bitIndexEntry, Gtk::PACK_SHRINK,5);
        bitTopBox.pack_start(*makeLabel("Бит (0/1):"), Gtk::PACK_SHRINK,5);
        bitTopBox.pack_start(bitValueEntry, Gtk::PACK_SHRINK,5);
        bitTopBox.pack_start(*makeLabel("Размер:"), Gtk::PACK_SHRINK,5);
        bitTopBox.pack_start(bitSizeEntry, Gtk::PACK_SHRINK,5);

        bitBottomBox.pack_start(bitSetButton, Gtk::PACK_SHRINK,5);
        bitBottomBox.pack_start(bitAndButton, Gtk::PACK_SHRINK,5);
        bitBottomBox.pack_start(bitOrButton, Gtk::PACK_SHRINK,5);
        bitBottomBox.pack_start(bitXorButton, Gtk::PACK_SHRINK,5);
        bitBottomBox.pack_start(bitNotButton, Gtk::PACK_SHRINK,5);

        bitPage.pack_start(bitTopBox, Gtk::PACK_SHRINK,5);
        bitPage.pack_start(bitScroll, Gtk::PACK_EXPAND_WIDGET,5);
        bitPage.pack_start(bitBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(bitPage, "BitSequence");

        
        funcBuffer = Gtk::TextBuffer::create();
        funcOutput.set_buffer(funcBuffer); funcOutput.set_editable(false);
        funcScroll.add(funcOutput);
        funcScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        funcScroll.set_hexpand(true); funcScroll.set_vexpand(true);

        seq1Box.pack_start(*makeLabel("Seq1:"), Gtk::PACK_SHRINK,5);
        seq1Box.pack_start(seq1Entry, Gtk::PACK_EXPAND_WIDGET,5);
        seq1Box.pack_start(seq1AddButton, Gtk::PACK_SHRINK,5);
        seq1Box.pack_start(seq1ClearButton, Gtk::PACK_SHRINK,5);

        seq2Box.pack_start(*makeLabel("Seq2:"), Gtk::PACK_SHRINK,5);
        seq2Box.pack_start(seq2Entry, Gtk::PACK_EXPAND_WIDGET,5);
        seq2Box.pack_start(seq2AddButton, Gtk::PACK_SHRINK,5);
        seq2Box.pack_start(seq2ClearButton, Gtk::PACK_SHRINK,5);

        funcButtonsBox.pack_start(mapButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(whereButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(reduceButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(zipButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(splitButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(iteratorsButton, Gtk::PACK_SHRINK,5);
        funcButtonsBox.pack_start(unzipButton, Gtk::PACK_SHRINK,5);

        funcBox.pack_start(seq1Box, Gtk::PACK_SHRINK,5);
        funcBox.pack_start(seq2Box, Gtk::PACK_SHRINK,5);
        funcBox.pack_start(funcButtonsBox, Gtk::PACK_SHRINK,5);
        funcBox.pack_start(funcScroll, Gtk::PACK_EXPAND_WIDGET,5);
        funcPage.pack_start(funcBox, Gtk::PACK_EXPAND_WIDGET,5);
        notebook.append_page(funcPage, "Map/Reduce");

        
        squareMatrixBuffer = Gtk::TextBuffer::create();
        squareMatrixOutput.set_buffer(squareMatrixBuffer);
        squareMatrixOutput.set_editable(false);
        squareMatrixScroll.add(squareMatrixOutput);
        squareMatrixScroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        squareMatrixScroll.set_hexpand(true); squareMatrixScroll.set_vexpand(true);

        squareMatrixTopBox.pack_start(*makeLabel("Размер:"), Gtk::PACK_SHRINK,5);
        squareMatrixTopBox.pack_start(matrixSizeEntry, Gtk::PACK_SHRINK,5);
        squareMatrixTopBox.pack_start(matrixCreateButton, Gtk::PACK_SHRINK,5);
        squareMatrixTopBox.pack_start(matrixInputGrid, Gtk::PACK_SHRINK,5);

        squareMatrixBottomBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
        squareMatrixBottomBox.set_spacing(5);
        squareMatrixBottomBox.pack_start(matrixAddButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixScalarButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(scalarEntry, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixNormButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixSwapRowsButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixMultiplyRowButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixAddRowButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixSwapColsButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixMultiplyColButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixAddColButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixMultiplyButton, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(*makeLabel("i/j/t/s:"), Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(rowIndexEntry, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(targetEntry, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(sourceEntry, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(*makeLabel("множитель:"), Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(factorEntry, Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(*makeLabel("Значения через пробел:"), Gtk::PACK_SHRINK,5);
        squareMatrixBottomBox.pack_start(matrixInitEntry, Gtk::PACK_EXPAND_WIDGET,5);
        squareMatrixBottomBox.pack_start(matrixInitButton, Gtk::PACK_SHRINK,5);

        squareMatrixPage.pack_start(squareMatrixTopBox, Gtk::PACK_SHRINK,5);
        squareMatrixPage.pack_start(squareMatrixScroll, Gtk::PACK_EXPAND_WIDGET,5);
        squareMatrixPage.pack_start(squareMatrixBottomBox, Gtk::PACK_SHRINK,5);
        notebook.append_page(squareMatrixPage, "SquareMatrix");

        
        arrayAppendButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayAppend));
        arrayPrependButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayPrepend));
        arrayInsertButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayInsert));
        arrayGetButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayGet));
        arrayConcatButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayConcat));
        arraySubseqButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArraySubseq));
        arrayClearButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onArrayClear));

        listAppendButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListAppend));
        listPrependButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListPrepend));
        listInsertButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListInsert));
        listGetButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListGet));
        listConcatButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListConcat));
        listSubseqButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListSubseq));
        listClearButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onListClear));

        mutableAppendButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMutableAppend));
        mutablePrependButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMutablePrepend));
        mutableInsertButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMutableInsert));

        immutableAppendButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onImmutableAppend));
        immutablePrependButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onImmutablePrepend));
        immutableInsertButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onImmutableInsert));

        bitSetButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onBitSet));
        bitAndButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onBitAnd));
        bitOrButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onBitOr));
        bitXorButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onBitXor));
        bitNotButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onBitNot));

        mapButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMap));
        whereButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onWhere));
        reduceButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onReduce));
        zipButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onZip));
        splitButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onSplit));

        seq1AddButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onSeq1Add));
        seq1ClearButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onSeq1Clear));
        seq2AddButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onSeq2Add));
        seq2ClearButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onSeq2Clear));

        iteratorsButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onDemoIterators));
        unzipButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onUnzip));

        matrixCreateButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixCreate));
        matrixInitButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixInit));
        matrixAddButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixAdd));
        matrixScalarButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixScalar));
        matrixNormButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixNorm));
        matrixSwapRowsButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixSwapRows));
        matrixMultiplyRowButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixMultiplyRow));
        matrixAddRowButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixAddRow));
        matrixSwapColsButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixSwapCols));
        matrixMultiplyColButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixMultiplyCol));
        matrixAddColButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixAddCol));
        matrixMultiplyButton.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::onMatrixMultiply));

        show_all_children();

        appendArrayOutput("Программа запущена");
        appendListOutput("Программа запущена");
        appendMutableOutput("Программа запущена");
        appendImmutableOutput("Программа запущена. Начальная последовательность: " + getSequenceString(immutableSeq));
        appendBitOutput("Программа запущена");
        appendFuncOutput("Программа запущена");
        appendParts("Вкладка SquareMatrix готова");
    }

    virtual ~MainWindow() {
        delete arraySeq; delete listSeq; delete mutableSeq; delete immutableSeq;
        delete bitSeq1; delete seq1; delete seq2;
        for (size_t i=0; i<matrixEntries.GetSize(); ++i)
            for (size_t j=0; j<matrixEntries.Get(i).GetSize(); ++j)
                delete matrixEntries.Get(i).Get(j);
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.lab2.app");
    MainWindow window;
    return app->run(window);
}