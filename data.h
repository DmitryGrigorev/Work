#ifndef DATA_H
#define DATA_H

#include <qglobal.h>

typedef quint8 Byte;   // 0..255
typedef quint16 Word;  // 0..65535
typedef quint32 DWord; // 0..4294967295

enum {
  RECTYPE = ((int)'Z' << 8) | 'Z',
  RECTYPE_NEW = ((int)'M' << 8) | 'W',
  RECTYPE_OLD = ((int)'M' << 8) | 'L',
};

/*!
  *
  */
typedef struct __attribute__((packed)) {
  Byte svar_flag;       //байт флагов режима сварки
  Byte tok_s;           //ток зажигания
  Word tok_i;           //ток импульса
  Word tok_p;           //ток паузы
  Byte produv;          //длительность продува
  Byte narastanie;      //длительность нарастания
  Byte time_i;          //длительность импульса
  Byte time_p;          //длительность паузы
  Byte time_s;          //длительность спада
  Byte time_obduv;      //время обдува
  Byte time_progrev;    //время прогрева
  Word skor_vresheniya; //скорость вращения
  Byte put_svarki;      //путь сварки
  Byte koridor_toka; //коридор тока                   //изменение 1.6
  Byte koridor_skorosti; //коридор скорости           //изменение 1.6
  Word svar;   //идентификатор сварщика
  DWord detal; //идентификатор детали                //изменение 1.6
  bool istochnic;
  DWord ip; //указатель на массив значений тока
  DWord sp; //указатель на массив значений скорости
  Word count;          //количество отсчетов в записи
  DWord error_count;   //ошибок в записи
  char name[30];       //имя записи
  double data_, time_; //дата и время
  bool notfree;        //признак занятости
  Word I_imp_min;      //изменение 1.6
  Word I_imp_max;      //изменение 1.6
  Word I_pause_min;    //изменение 1.6
  Word I_pause_max;    //изменение 1.6
  Word V_min;          //изменение 1.6
  Word V_max;          //изменение 1.6
  char code[10];       //изменение 1.9
  Byte reserved[5];
  double koridor_toka_plus, koridor_toka_minus; //изменение 1.9
  double koridor_skor_plus, koridor_skor_minus; //изменение 1.9
} Record;

struct __attribute((packed)) NewRecord {
  Byte svar_flag;       //байт флагов режима сварки
  Byte tok_s;           //ток зажигания
  Word tok_i;           //ток импульса
  Word tok_p;           //ток паузы
  Byte produv;          //длительность продува
  Byte narastanie;      //длительность нарастания
  Byte time_i;          //длительность импульса
  Byte time_p;          //длительность паузы
  Byte time_s;          //длительность спада
  Byte time_obduv;      //время обдува
  Byte time_progrev;    //время прогрева
  Word skor_vresheniya; //скорость вращения
  Byte put_svarki;      //путь сварки
  Byte koridor_toka; //коридор тока                   //изменение 1.6
  Byte koridor_skorosti; //коридор скорости           //изменение 1.6
  Word svar;   //идентификатор сварщика
  DWord detal; //идентификатор детали                //изменение 1.6
  bool istochnic;
  DWord ip; //указатель на массив значений тока
  DWord sp; //указатель на массив значений скорости
  Word count;          //количество отсчетов в записи
  DWord error_count;   //ошибок в записи
  char name[30];       //имя записи
  double data_, time_; //дата и время
  bool notfree;        //признак занятости
  Word I_imp_min;      //изменение 1.6
  Word I_imp_max;      //изменение 1.6
  Word I_pause_min;    //изменение 1.6
  Word I_pause_max;    //изменение 1.6
  Word V_min;          //изменение 1.6
  Word V_max;          //изменение 1.6
  Byte reserved[16];
};

typedef struct __attribute__((packed)) {
  Byte svar_flag;       //байт флагов режима сварки
  Byte tok_s;           //ток зажигания
  Word tok_i;           //ток импульса
  Word tok_p;           //ток паузы
  Byte produv;          //длительность продува
  Byte narastaniebyte;  //длительность нарастания
  Byte time_i;          //длительность импульса
  Byte time_p;          //длительность паузы
  Byte time_s;          //длительность спада
  Byte time_obduv;      //время обдува
  Byte time_progrev;    //время прогрева
  Word skor_vresheniya; //скорость вращения
  Byte put_svarki;      //путь сварки
  Word svar;            //идентификатор сварщика
  Word detal;           //идентификатор детали
  bool istochnic;
  DWord ip; //указатель на массив значений тока
  DWord sp; //указатель на массив значений скорости
  Word count;          //количество отсчетов в записи
  DWord error_count;   //ошибок в записи
  char name[30];       //имя записи
  double data_, time_; //дата и время
  bool notfree;        //признак занятости
  Byte reserved[16];
} OldRecord;
#endif // DATA_H
