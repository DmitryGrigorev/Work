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
  Byte svar_flag;       //���� ������ ������ ������
  Byte tok_s;           //��� ���������
  Word tok_i;           //��� ��������
  Word tok_p;           //��� �����
  Byte produv;          //������������ �������
  Byte narastanie;      //������������ ����������
  Byte time_i;          //������������ ��������
  Byte time_p;          //������������ �����
  Byte time_s;          //������������ �����
  Byte time_obduv;      //����� ������
  Byte time_progrev;    //����� ��������
  Word skor_vresheniya; //�������� ��������
  Byte put_svarki;      //���� ������
  Byte koridor_toka; //������� ����                   //��������� 1.6
  Byte koridor_skorosti; //������� ��������           //��������� 1.6
  Word svar;   //������������� ��������
  DWord detal; //������������� ������                //��������� 1.6
  bool istochnic;
  DWord ip; //��������� �� ������ �������� ����
  DWord sp; //��������� �� ������ �������� ��������
  Word count;          //���������� �������� � ������
  DWord error_count;   //������ � ������
  char name[30];       //��� ������
  double data_, time_; //���� � �����
  bool notfree;        //������� ���������
  Word I_imp_min;      //��������� 1.6
  Word I_imp_max;      //��������� 1.6
  Word I_pause_min;    //��������� 1.6
  Word I_pause_max;    //��������� 1.6
  Word V_min;          //��������� 1.6
  Word V_max;          //��������� 1.6
  char code[10];       //��������� 1.9
  Byte reserved[5];
  double koridor_toka_plus, koridor_toka_minus; //��������� 1.9
  double koridor_skor_plus, koridor_skor_minus; //��������� 1.9
} Record;

struct __attribute((packed)) NewRecord {
  Byte svar_flag;       //���� ������ ������ ������
  Byte tok_s;           //��� ���������
  Word tok_i;           //��� ��������
  Word tok_p;           //��� �����
  Byte produv;          //������������ �������
  Byte narastanie;      //������������ ����������
  Byte time_i;          //������������ ��������
  Byte time_p;          //������������ �����
  Byte time_s;          //������������ �����
  Byte time_obduv;      //����� ������
  Byte time_progrev;    //����� ��������
  Word skor_vresheniya; //�������� ��������
  Byte put_svarki;      //���� ������
  Byte koridor_toka; //������� ����                   //��������� 1.6
  Byte koridor_skorosti; //������� ��������           //��������� 1.6
  Word svar;   //������������� ��������
  DWord detal; //������������� ������                //��������� 1.6
  bool istochnic;
  DWord ip; //��������� �� ������ �������� ����
  DWord sp; //��������� �� ������ �������� ��������
  Word count;          //���������� �������� � ������
  DWord error_count;   //������ � ������
  char name[30];       //��� ������
  double data_, time_; //���� � �����
  bool notfree;        //������� ���������
  Word I_imp_min;      //��������� 1.6
  Word I_imp_max;      //��������� 1.6
  Word I_pause_min;    //��������� 1.6
  Word I_pause_max;    //��������� 1.6
  Word V_min;          //��������� 1.6
  Word V_max;          //��������� 1.6
  Byte reserved[16];
};

typedef struct __attribute__((packed)) {
  Byte svar_flag;       //���� ������ ������ ������
  Byte tok_s;           //��� ���������
  Word tok_i;           //��� ��������
  Word tok_p;           //��� �����
  Byte produv;          //������������ �������
  Byte narastaniebyte;  //������������ ����������
  Byte time_i;          //������������ ��������
  Byte time_p;          //������������ �����
  Byte time_s;          //������������ �����
  Byte time_obduv;      //����� ������
  Byte time_progrev;    //����� ��������
  Word skor_vresheniya; //�������� ��������
  Byte put_svarki;      //���� ������
  Word svar;            //������������� ��������
  Word detal;           //������������� ������
  bool istochnic;
  DWord ip; //��������� �� ������ �������� ����
  DWord sp; //��������� �� ������ �������� ��������
  Word count;          //���������� �������� � ������
  DWord error_count;   //������ � ������
  char name[30];       //��� ������
  double data_, time_; //���� � �����
  bool notfree;        //������� ���������
  Byte reserved[16];
} OldRecord;
#endif // DATA_H
