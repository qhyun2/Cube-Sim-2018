#ifndef TEST_H
#define TEST_H


class Test
{
    public:
        Test();
        virtual ~Test();
        int*** Getturns[6]() { return turns[6]; }
        void Setturns[6](int*** val) { turns[6] = val; }
    protected:
    private:
        int*** turns[6];
};

#endif // TEST_H
