#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace nspace
{
    struct Data
    {
        double key1;
        long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct DoubleIO
    {
        double& ref;
    };

    struct LongLIO
    {
        long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct LabelIO
    {
        std::string exp;
    };

    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, LongLIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, Data& dest);
    std::ostream& operator<<(std::ostream& out, const Data& dest);

    void sort(std::vector< nspace::Data > Items[], size_t size);
    bool sorted(std::vector< nspace::Data > Items[], size_t size);

}



int main()
{
    using nspace::Data;

    std::vector< Data > data;
    std::istringstream iss("{ \"key1\": 20D, \"key2\": 89l,\"key3\": \"Just started learning github\" }");

    std::copy(
        std::istream_iterator< Data >(iss),
        std::istream_iterator< Data >(),
        std::back_inserter(data)
    );


    std::vector< Data > data2;
    std::istringstream iss2("{ \"key1\": 15D, \"key2\": 21l,\"key3\": \"Git Lab T2\" }");

    std::copy(
        std::istream_iterator< Data >(iss2),
        std::istream_iterator< Data >(),
        std::back_inserter(data2)
    );


    std::vector< Data > data3;
    std::istringstream iss3("{ \"key1\": 3D, \"key2\": 34l,\"key3\": \"Git Lab T3\" }");

    std::copy(
        std::istream_iterator< Data >(iss3),
        std::istream_iterator< Data >(),
        std::back_inserter(data3)
    );


    std::vector< Data > data4;
    std::istringstream iss4("{ \"key1\": 3D, \"key2\": 38l,\"key3\": \"Git Lab dublicate\" }");

    std::copy(
        std::istream_iterator< Data >(iss4),
        std::istream_iterator< Data >(),
        std::back_inserter(data4)
    );



    std::cout << "\nsorting data items\n";
    std::vector< Data > DItems[4] = { data, data2, data3, data4 };

    for (size_t i = 0; i < 4; ++i) {
        std::copy(
            std::begin(DItems[i]),
            std::end(DItems[i]),
            std::ostream_iterator< Data >(std::cout, "\n")
        );
    }
    std::cout << "\n";

    sort(DItems, 4);
    for (size_t i = 0; i < 4; ++i) {
        std::copy(
            std::begin(DItems[i]),
            std::end(DItems[i]),
            std::ostream_iterator< Data >(std::cout, "\n")
        );
    }

    return 0;
}


namespace nspace
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, DoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'D' };
    }

    std::istream& operator>>(std::istream& in, LongLIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref >> DelimiterIO{ 'l' };
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string data = "";
        if ((in >> StringIO{ data }) && (data != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Data& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        Data input;
        {
            using sep = DelimiterIO;
            using label = LabelIO;
            using dbl = DoubleIO;
            using ll = LongLIO;
            using str = StringIO;
            in >> sep{ '{' };
            in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
            in >> sep{ ',' };
            in >> label{ "key2" } >> sep{ ':' } >> ll{ input.key2 };
            in >> sep{ ',' };
            in >> label{ "key3" } >> sep{ ':' } >> str{ input.key3 };
            in >> sep{ '}' };
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Data& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
        out << ":key2 " << std::fixed << std::setprecision(1) << src.key2 << "ll";
        out << ":key3 " << "\"" << src.key3 << "\"";
        out << ":)";
        return out;
    }

    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    iofmtguard::~iofmtguard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }


    bool sorted(std::vector< nspace::Data > Items[], size_t size) {
        bool isOrdered = true;
        for (size_t i = 0; i < size - 1; ++i) {
            auto b = Items[i].begin();
            if (b->key1 > Items[i + 1].begin()->key1) isOrdered = false;
            else if (b->key2 > Items[i + 1].begin()->key2 && b->key1 == Items[i + 1].begin()->key1) isOrdered = false;
            else if (b->key3.length() > Items[i + 1].begin()->key3.length() && b->key2 == Items[i + 1].begin()->key2) isOrdered = false;
        }
        return isOrdered;
    }
    void sort(std::vector< nspace::Data > Items[], size_t size) {
        for (size_t i = 0; i <= size - 1; ++i) {

            for (size_t j = i + 1; j <= size - 1; ++j) {

                if (Items[i].begin()->key1 > Items[j].begin()->key1) {
                    std::vector< nspace::Data > temp = Items[i];
                    Items[i] = Items[j];
                    Items[j] = temp;
                }
                else if ((Items[i].begin()->key2 > Items[j].begin()->key2 && Items[i].begin()->key1 == Items[j].begin()->key1) ||
                    (Items[i].begin()->key2 > Items[j].begin()->key2 && Items[i].begin()->key1 < Items[j].begin()->key1)) {
                    std::vector< nspace::Data > temp = Items[i];
                    Items[i] = Items[j];
                    Items[j] = temp;
                }
                else if (Items[i].begin()->key3.length() > Items[j].begin()->key3.length()
                    ) {
                    std::vector< nspace::Data > temp = Items[i];
                    Items[i] = Items[j];
                    Items[j] = temp;
                }
            }
        }
    }
}


