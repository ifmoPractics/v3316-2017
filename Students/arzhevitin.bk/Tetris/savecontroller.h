#pragma once

#include "tetrismodel.h"

#include <fstream>
#include <QSettings>
#include <QPoint>

///=============================================================================
struct SaveController
{
    static bool saveGame(TetrisModel& tm);
    static bool loadGame(TetrisModel& tm);
    static bool removeGame();
    static void saveRecord(int s1, int l1, int s2, int l2, int s3, int l3);
    static void loadRecord(int &s1, int &l1, int &s2, int &l2, int &s3, int &l3);


private:
    static const char* FILENAME_SAVE;
};


///----------------------------------------------------------------------------
const char* SaveController::FILENAME_SAVE = "save.data";

bool SaveController::saveGame(TetrisModel &tm)
{
    tetrismodel::Matrix field, fieldItem;
    TetrisItem activeItem;
    int score, level, touch;
    int sizeIField, sizeJField, sizeIFieldItem, sizeJFieldItem, pointX, pointY;
    bool state;
    QPoint point;
    tm.getData(field, activeItem, score, level, state);
    activeItem.getData(fieldItem, point, touch);

    std::ofstream ofile(SaveController::FILENAME_SAVE, std::ios::binary);

    //Запись размера матрицы поля
    sizeIField = field.size();
    sizeJField = (sizeIField < 0) ? 0 :field[0].size();
    ofile.write((char*)&sizeIField, sizeof(int));
    ofile.write((char*)&sizeJField, sizeof(int));
    //Запись матрицы поля
    for (int i(0); i < sizeIField; ++i) {
        for (int j(0); j < sizeJField; ++j) {
            ofile.write((char*)&field[i][j], sizeof(tetrismodel::FCT));
        }
    }
    //Запись счета
    ofile.write((char*)&score, sizeof(int));
    //Запись уровня
    ofile.write((char*)&level, sizeof(int));
    //Запись состояния
    ofile.write((char*)&state, sizeof(bool));
    //Запись активного элемента
    /// Запись размера матрицы активного элемента
    sizeIFieldItem = fieldItem.size();
    sizeJFieldItem = fieldItem[0].size();
    ofile.write((char*)&sizeIFieldItem, sizeof(int));
    ofile.write((char*)&sizeJFieldItem, sizeof(int));
    ///Запись матрицы активного элемента
    for (int i(0); i < sizeIFieldItem; ++i) {
        for (int j(0); j < sizeJFieldItem; ++j) {
            ofile.write((char*)&fieldItem[i][j], sizeof(tetrismodel::FCT));
        }
    }
    ///Запись текущей точки активного элемента
    pointX = point.x();
    pointY = point.y();
    ofile.write((char*)&pointX, sizeof(int));
    ofile.write((char*)&pointY, sizeof(int));
    ///Запись касаний активного элемента
    ofile.write((char*)&touch, sizeof(int));

    if (!ofile) { return false; }
    ofile.close();

    return true;
}

bool SaveController::loadGame(TetrisModel &tm)
{
    tetrismodel::Matrix field, fieldItem;
    TetrisItem activeItem;
    int score, level, touch;
    int sizeIField, sizeJField, sizeIFieldItem, sizeJFieldItem, pointX, pointY;
    bool state;
    QPoint point;

    std::ifstream ifile(SaveController::FILENAME_SAVE, std::ios::binary);
    if (!ifile) {return false;}

    //Чтение
    ifile.read((char*)&sizeIField, sizeof(int));
    if(ifile.eof()) { return false; }
    ifile.read((char*)&sizeJField, sizeof(int));
    for (int i(0); i < sizeIField; ++i) {
        QVector<tetrismodel::FCT> tmpV;
        for (int j(0); j < sizeJField; ++j) {
            tetrismodel::FCT tmpFCT;
            ifile.read((char*)&tmpFCT, sizeof(tetrismodel::FCT));
            tmpV.push_back(tmpFCT);
        }
        field.push_back(tmpV);
    }
    ifile.read((char*)&score, sizeof(int));
    ifile.read((char*)&level, sizeof(int));
    ifile.read((char*)&state, sizeof(bool));
    ifile.read((char*)&sizeIFieldItem, sizeof(int));
    ifile.read((char*)&sizeJFieldItem, sizeof(int));
    for (int i(0); i < sizeIFieldItem; ++i) {
        QVector<tetrismodel::FCT> tmpV;
        for (int j(0); j < sizeJFieldItem; ++j) {
            tetrismodel::FCT tmpFCT;
            ifile.read((char*)&tmpFCT, sizeof(tetrismodel::FCT));
            tmpV.push_back(tmpFCT);
        }
        fieldItem.push_back(tmpV);
    }
    ifile.read((char*)&pointX, sizeof(int));
    ifile.read((char*)&pointY, sizeof(int));
    point.setX(pointX);
    point.setY(pointY);
    ifile.read((char*)&touch, sizeof(int));

    tm.setData(field, activeItem, score, level, state);
    activeItem.setData(fieldItem, point, touch);

    ifile.close();

    return true;
}

bool SaveController::removeGame()
{
    return remove(FILENAME_SAVE);
}

void SaveController::saveRecord(int s1, int l1, int s2, int l2, int s3, int l3)
{
    QSettings settings("MonkeyCo", "Tetris");
    settings.beginGroup("/game_records");
    settings.setValue("/s1", s1);
    settings.setValue("/l1", l1);
    settings.setValue("/s2", s2);
    settings.setValue("/l2", l2);
    settings.setValue("/s3", s3);
    settings.setValue("/l3", l3);
    settings.endGroup();
}

void SaveController::loadRecord(int &s1, int &l1, int &s2, int &l2, int &s3, int &l3)
{
    QSettings settings("MonkeyCo", "Tetris");
    settings.beginGroup("/game_records");

    s1 = settings.value("/s1", 0).toInt();
    l1 = settings.value("/l1", 0).toInt();
    s2 = settings.value("/s2", 0).toInt();
    l2 = settings.value("/l2", 0).toInt();
    s3 = settings.value("/s3", 0).toInt();
    l3 = settings.value("/l3", 0).toInt();
    settings.endGroup();
}
