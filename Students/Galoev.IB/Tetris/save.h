#ifndef SAVE_H
#define SAVE_H

#include <vector>
#include <QSettings>

struct Parametrs{
    Parametrs(){}
    Parametrs(std::vector< std::vector<int> > field, int score, int num_cur, int num_next, bool gameOver)
        : m_score(score), m_num_cur(num_cur), m_num_next(num_next), m_gameOver(gameOver){
        m_field.resize(20);
        for (int i=0; i<20; ++i)
            m_field[i].resize(10);
        for (int i=0; i<20; ++i)
            for (int j=0; j<10; ++j)
                m_field[i][j]=field[i][j];
    }

    int m_score;
    int m_num_cur;
    int m_num_next;
    bool m_gameOver;
    std::vector< std::vector<int> > m_field;
};

struct Record{
    Record(){}
    Record(QString name, int score, int place): m_name(name), m_score(score), m_place(place) {}
    QString m_name;
    int m_score;
    int m_place;
};


class Save
{
public:
    void saveGame(const Parametrs&);
    Parametrs loadGame();
    void saveRecord(const Record&);
    Record loadRecord(int);
};

#endif // SAVE_H
