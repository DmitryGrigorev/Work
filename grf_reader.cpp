#include "grf_reader.h"
#include "mainwindow.h"

/**
 * @brief GRF_Reader::GRF_Reader
 * @param file_name
 *
 * ������� ������ �����, �������� ���� � ������ ������ � ������.
 * ����� �������� ���������� ����� � ����� memfile.
 */
GRF_Reader::GRF_Reader(QString &file_name) {
  utf_codec = QTextCodec::codecForName("Windows-1251");
  memfile = NULL;
  stream = NULL;
  error_flag = false;             //������ ���
  grf_fil = new QFile(file_name); //������� ������ �����
  if (grf_fil->exists()) {
    grf_fil->open(
        QIODevice::ReadWrite); //��������� ���� � ������ ������ � ������
    memfile = new QByteArray(grf_fil->readAll()); //�������� ���� � ������
    stream = new QDataStream(memfile, QIODevice::ReadWrite); //������ ������
    //���������� �����
    //������ � �����
    // memfile
    stream->setByteOrder(
        QDataStream::LittleEndian); //������������ ������ ������� ���� � ������

    *stream >> records_type; //�������� ��� �������
    *stream >> record_count; //�������� ���������� �������
                             /*
                                                   * ��������� ����� ������� � ��� �� ������������
                                                   */
    if (record_count < 1000 &&
        (records_type == RECTYPE || records_type == RECTYPE_NEW ||
         records_type == RECTYPE_OLD)) {
      //((MainWindow *)parent_wdg_ptr)
      //    ->setStatusLabelText(
      //        "���� �������� ��������"); //������� ����� ������ � statusbar
    } else {
      error_flag = true;
      //((MainWindow *)parent_wdg_ptr)
      //    ->setStatusLabelText(
      //        "����������� ������ �����"); //������� ����� ������ � statusbar
    }
  } else {
    error_flag =
        true; //���� ����� �� ����������, �� ������������� ������� ������
    //((MainWindow *)parent_wdg_ptr)
    //    ->setStatusLabelText(
    //        "������ ������ �����"); //������� ����� ������ � statusbar
    delete grf_fil;
  }
}

/*!
 * \brief GRF_Reader::~GRF_Reader ���������� ������. ������� ��� ���� ������.
 */
GRF_Reader::~GRF_Reader() {
  /* ��������� ����� �����/������ � ����� */
  this->stream->unsetDevice();
  this->stream->resetStatus();
  /* ������ ��������� �� ������ ������ */
  delete this->stream;
  /* ������ ����� ����� */
  this->memfile->clear();
  /* ������ ��������� �� ����� */
  delete this->memfile;

  /* ������ � ������ ������� �������, ����������� � ������ */
  for (int i = 0; i < record_count; i++) {
    if (records_type == RECTYPE) {
      this->recs[i].currency_array->clear();
      this->recs[i].speed_array->clear();
      delete this->recs[i].r;
    }
    if (records_type == RECTYPE_NEW) {
      this->newrecs[i].currency_array->clear();
      this->newrecs[i].speed_array->clear();
      delete this->newrecs[i].r;
    }
    if (records_type == RECTYPE_OLD) {
      this->oldrecs[i].currency_array->clear();
      this->oldrecs[i].speed_array->clear();
      delete this->oldrecs[i].r;
    }
  }
  if (records_type == RECTYPE) {
    delete this->recs;
  }
  if (records_type == RECTYPE_NEW) {
    delete this->newrecs;
  }
  if (records_type == RECTYPE_OLD) {
    delete this->oldrecs;
  }
}

/**
* @brief GRF_Reader::SetParentWidgetPointer    ���������� ��������� �� ������
* ������������� ����
* @param w ���������
*/
void GRF_Reader::SetParentWidgetPointer(void *w) { this->parent_wdg_ptr = w; }

#include "mainwindow.h"

/*!
 * \brief GRF_Reader::BeginReading
 */
void GRF_Reader::BeginReading(void *w) {
  /*
 *  �� ���� �������, ���������� �� �����, �������� ������ ��� ������������
 * ������
 */
  MainWindow *wnd = reinterpret_cast<MainWindow *>(w);
  if (records_type == RECTYPE)
    this->recs = new st_record<Record>[record_count];
  if (records_type == RECTYPE_NEW)
    this->newrecs = new st_record<NewRecord>[record_count];
  if (records_type == RECTYPE_OLD)
    this->oldrecs = new st_record<OldRecord>[record_count];
  /*
   * ���� ���������� ������� � ������.
   * �� ���� ������ ���������� ��� � ���� ���� ���������.
   * ����� ������ ����� ������, ������� ����� ��� ������ ������� � ����.
   * ����� �������� �������.
   */
  for (int i = 0; i < record_count; i++) {
    if (records_type == RECTYPE) {
      ReadRecord(&recs[i]);
      wnd->SetTable(recs[i].r);
    }
    if (records_type == RECTYPE_NEW) {
      ReadRecord(&newrecs[i]);
      wnd->SetTable(newrecs[i].r);
    }
    if (records_type == RECTYPE_OLD) {
      ReadRecord(&oldrecs[i]);
      wnd->SetTable(oldrecs[i].r);
    }
  }
}

/*!
 * \brief GRF_Reader::ReadRecord
 * \param record
 * ������� ��������� ���� ������ �� ����� ��������
 */
void GRF_Reader::ReadRecord(st_record<Record> *record) {
  record->currency_array = NULL;
  record->r = new Record();
  record->speed_array = NULL;
  // �������� ���� ������
  stream->readRawData((char *)record->r, sizeof(Record));
  // ������� ����� ��� �������
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  // �������� �������
  stream->readRawData((char *)record->currency_array->data(),
                      sizeof(quint16) * record->r->count);
  stream->readRawData((char *)record->speed_array->data(),
                      sizeof(quint16) * record->r->count);
  quint16 t;
  *stream >> t;
}

/*!
 * \brief GRF_Reader::ReadRecord
 * \param record
 */
void GRF_Reader::ReadRecord(st_record<NewRecord> *record) {
  record->currency_array = NULL;
  record->r = new NewRecord();
  record->speed_array = NULL;
  //�������� ���� ������
  stream->readRawData((char *)record->r, sizeof(NewRecord));
  // ������� ����� ��� �������
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  //�������� �������
  stream->readRawData((char *)record->currency_array->data(),
                      sizeof(quint16) * record->r->count);
  stream->readRawData((char *)record->speed_array->data(),
                      sizeof(quint16) * record->r->count);
  quint8 t;
  *stream >> t;
}
/*!
 * \brief GRF_Reader::ReadRecord
 * \param record
 */
void GRF_Reader::ReadRecord(st_record<OldRecord> *record) {
  record->currency_array = NULL;
  record->r = new OldRecord();
  record->speed_array = NULL;
  //�������� ���� ������
  stream->readRawData((char *)record->r, sizeof(NewRecord));
  // ������� ����� ��� �������
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  //�������� �������
  for (int j = 0; j < 2 * record->r->count; j++) {
    if (j < record->r->count)
      stream->readRawData((char *)&record->currency_array[j], 2);
    else
      stream->readRawData((char *)&record->speed_array[j], 2);
  }
}
