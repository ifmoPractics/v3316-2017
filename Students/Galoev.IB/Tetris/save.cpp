#include "save.h"

void Save::saveGame(const Parametrs & param){
    QSettings setting("Galoev", "Tetris");
    setting.beginGroup("Settings_Game");
    setting.setValue("score", param.m_score);
    setting.setValue("num_cur", param.m_num_cur);
    setting.setValue("num_next", param.m_num_next);
    setting.setValue("gameOver", param.m_gameOver);

    setting.beginWriteArray("field_Y", 20);
    for (int i=0; i<20; ++i){
        setting.setArrayIndex(i);
        setting.beginWriteArray("field_X", 10);
        for (int j=0; j<10; ++j){
            setting.setArrayIndex(j);
            setting.setValue("field_val", param.m_field[i][j]);
        }
        setting.endArray();
    }
    setting.endArray();
    setting.endGroup();
}

Parametrs Save::loadGame(){
    QSettings setting("Galoev", "Tetris");
    setting.beginGroup("Settings_Game");

    std::vector<std::vector<int> > field;
    field.resize(20);
    for (int i=0; i<20; ++i)
        field[i].resize(10);
    int score;
    int num_cur;
    int num_next;
    bool gameOver;

    score = setting.value("score", 0).toInt();
    num_cur = setting.value("num_cur", 0).toInt();
    num_next = setting.value("num_next", 0).toInt();
    gameOver = setting.value("gameOver", true).toBool();

    setting.beginReadArray("field_Y");
    for (int i=0; i<20; ++i){
        setting.setArrayIndex(i);
        setting.beginReadArray("field_X");
        for (int j=0; j<10; ++j){
            setting.setArrayIndex(j);
            field[i][j] = setting.value("field_val", 0).toInt();
        }
        setting.endArray();
    }
    setting.endArray();

    setting.endGroup();
    return Parametrs(field, score, num_cur, num_next, gameOver);
}

void Save::saveRecord(const Record & rec){
    QSettings setting("Galoev", "Tetris");
    setting.beginGroup("Settings_Record");
    setting.beginGroup("record"+QString::number(rec.m_place));
    setting.setValue("name", rec.m_name);
    setting.setValue("score", rec.m_score);
    setting.endGroup();
    setting.endGroup();
}

Record Save::loadRecord(int i){
    Record rec;
    rec.m_place = i;
    QSettings setting("Galoev", "Tetris");
    setting.beginGroup("Settings_Record");
    setting.beginGroup("record" + QString::number(i));
    rec.m_name=setting.value("name", "NONE").toString();
    rec.m_score=setting.value("score", 0).toInt();
    setting.endGroup();
    setting.endGroup();
    return rec;
}

