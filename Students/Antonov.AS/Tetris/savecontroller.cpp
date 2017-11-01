#include "savecontroller.h"

Record& Record::operator=(const Record& other){
    if (this != &other){
        this->place = other.place;
        this->name = other.place;
        this->score = other.score;
        this->line = other.line;
    }
    return *this;
}

SaveParameters::SaveParameters(QString m[17][10], int l, int s, QChar t, Coordinate c[4], QChar nextT){
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 10; j++){
            matrix[i][j] = m[i][j];
        }
    }
    for (int i = 0; i < 4; i++){
        coordinate[i] = c[i];
    }
    line = l;
    score = s;
    type = t;
    nextType = nextT;
}

SaveParameters::SaveParameters(const SaveParameters& other){
    for (int i = 0; i < 17; i++){
        for (int j = 0; j < 10; j++){
            matrix[i][j] = other.matrix[i][j];
        }
    }
    for (int i = 0; i < 4; i++){
        coordinate[i] = other.coordinate[i];
    }
    line = other.line;
    score = other.score;
    type = other.type;
    nextType = other.nextType;
}

SaveParameters& SaveParameters::operator=(const SaveParameters& other){
    if (this != &other){
        for (int i = 0; i < 17; i++){
            for (int j = 0; j < 10; j++){
                matrix[i][j] = other.matrix[i][j];
            }
        }
        for (int i = 0; i < 4; i++){
            coordinate[i] = other.coordinate[i];
        }
        line = other.line;
        score = other.score;
        type = other.type;
        nextType = other.nextType;
    }
    return *this;
}

void SaveController::save(const SaveParameters& parameters){
    QSettings setting("MyCompany", "Tetris");

    setting.beginWriteArray("matrixI", 17);
        for (int i = 0; i < 17; i++){
            setting.setArrayIndex(i);
            setting.beginWriteArray("matrixJ", 10);
                for (int j = 0; j < 10; j++){
                    setting.setArrayIndex(j);
                    setting.setValue("matrixValue", parameters.matrix[i][j]);
                }
            setting.endArray();
        }
    setting.endArray();

    setting.beginWriteArray("figureCoordinates", 4);
    for (int i = 0; i < 4; i++){
        setting.setArrayIndex(i);
        setting.setValue("xCoordinate", parameters.coordinate[i].x);
        setting.setValue("yCoordinate", parameters.coordinate[i].y);
    }
    setting.endArray();
    setting.setValue("figureType", parameters.type);
    setting.setValue("nextFigureType", parameters.nextType);

    setting.setValue("line", parameters.line);
    setting.setValue("score", parameters.score);
}


SaveParameters SaveController::load(){
    QSettings setting("MyCompany", "Tetris");
    QString matrix[17][10];
    Coordinate coordinate[4];
    int line;
    int score;
    QChar type;
    QChar nextType;

    setting.beginReadArray("matrixI");
        for (int i = 0; i < 17; i++){
            setting.setArrayIndex(i);
            setting.beginReadArray("matrixJ");
                for (int j = 0; j < 10; j++){
                    setting.setArrayIndex(j);
                    matrix[i][j] = setting.value("matrixValue").toString();
                }
            setting.endArray();
        }
    setting.endArray();

    setting.beginReadArray("figureCoordinates");
    for (int i = 0; i < 4; i++){
        setting.setArrayIndex(i);
        coordinate[i].x = setting.value("xCoordinate").toInt();
        coordinate[i].y = setting.value("yCoordinate").toInt();
    }
    setting.endArray();
    type = setting.value("figureType").toChar();
    nextType = setting.value("nextFigureType").toChar();

    line = setting.value("line").toInt();
    score = setting.value("score").toInt();

    return SaveParameters(matrix, line, score, type, coordinate, nextType);
}

void SaveController::saveContinueStatus(bool status){
    QSettings setting("MyCompany", "Tetris");
    setting.setValue("continueStatus", status);
}

bool SaveController::loadContinueStatus(){
    QSettings setting("MyCompany", "Tetris");
    return setting.value("continueStatus").toBool();
}

void SaveController::saveRecord(const Record& record){
    QSettings setting("MyCompany", "Tetris");
    setting.beginGroup("place" + QString::number(record.place));
        setting.setValue("name", record.name);
        setting.setValue("score", record.score);
        setting.setValue("line", record.line);
    setting.endGroup();
}

Record SaveController::getRecord(int n){
    Record record;
    record.place = n;
    QSettings setting("MyCompany", "Tetris");
    setting.beginGroup("place" + QString::number(record.place));
        record.name = setting.value("name").toString();
        record.score = setting.value("score").toInt();
        record.line = setting.value("line").toInt();
    setting.endGroup();
    return record;
}

void SaveController::refreshRecords(){
    QSettings setting("MyCompany", "Tetris");
    for (int i = 0; i < 10; i++){
        setting.beginGroup("place" + QString::number(i + 1));
        setting.setValue("name", "NONE");
        setting.setValue("score", 0);
        setting.setValue("line", 0);
        setting.endGroup();
    }
}
