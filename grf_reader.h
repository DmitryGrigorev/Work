#ifndef GRF_READER_H
#define GRF_READER_H

#include "data.h"
#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QObject>
#include <QTextCodec>
#include <QVector>

#define MAX_RECS 100

/**
 *  @brief st_record struct ��������� ��� ���������� ������� ������, ����������
 * � ����� *.grf.
 */
template <typename T> struct st_record {
  /*!
   * \brief r ��������� �� ������
   */
  T *r;
  /*!
   * \brief currency_array ������ �����
   */
  QVector<quint16> *currency_array;
  /*!
   * \brief speed_array ������ ���������
   */
  QVector<quint16> *speed_array;
};
/**
 * @brief GRF_Reader class ��������� ������, ��� ���������� ������� � �������
 * ��� ������ � ����� *.grf
 */
class GRF_Reader {
public:
  GRF_Reader(QString &file_name); /// ����������� ������
  ~GRF_Reader();
  void SetParentWidgetPointer(void *w);
  /*!
   * \brief BeginReading  ������ ������ ����� ��������
   */
  void BeginReading(void *w);
  /*!
   * \brief ReadRecord    ������ ���� ������
   * \param r ��������� �� ������ ������ ���� Record
   */
  void ReadRecord(st_record<Record> *r);
  /*!
   * \brief ReadRecord    ������ ���� ������
   * \param r ��������� �� ������ ������ ���� NewRecord
   */
  void ReadRecord(st_record<NewRecord> *r);
  /*!
   * \brief ReadRecord    ������ ���� ������
   * \param r ��������� �� ������ ������ ���� OldRecord
   */
  void ReadRecord(st_record<OldRecord> *r);

private:
  /*!
   * ������ ������� ���� Record
   */
  st_record<Record> *recs;
  /*!
   * ������ ������� ���� NewRecord
   */
  st_record<NewRecord> *newrecs;
  /*!
   * ������ ������� ���� OldRecord
   */
  st_record<OldRecord> *oldrecs;
  /*!
   * ��������� �� ������ �����
   */
  QFile *grf_fil;
  /*!
   * ������� ������� ������
   */
  bool error_flag;
  /*!
   * ��������� �� ������ ������������� ����
   */
  void *parent_wdg_ptr;
  /*!
   * ��������� �� ����� ����� � ������
   */
  QByteArray *memfile;
  /*!
   * ��������� �� ������ ���������� �����/������
   */
  QDataStream *stream;
  /*!
   * ���������� �������
   */
  quint16 record_count;
  /*!
   * ��� �������
   */
  quint16 records_type;
  /*!
   * ��������� �� ������ ��������� Windows-1251.
   * ������������ ��� �������������� � Unicode.
   */
  QTextCodec *utf_codec;
};

#endif // GRF_READER_H
