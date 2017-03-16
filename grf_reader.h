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
 *  @brief st_record struct Структура для описывания единицы записи, хранищейся
 * в файле *.grf.
 */
template <typename T> struct st_record {
  /*!
   * \brief r указатель на запись
   */
  T *r;
  /*!
   * \brief currency_array массив токов
   */
  QVector<quint16> *currency_array;
  /*!
   * \brief speed_array массив скоростей
   */
  QVector<quint16> *speed_array;
};
/**
 * @brief GRF_Reader class Структура данных, для описывания свойств и методов
 * для работы с файла *.grf
 */
class GRF_Reader {
public:
  GRF_Reader(QString &file_name); /// Конструктор класса
  ~GRF_Reader();
  void SetParentWidgetPointer(void *w);
  /*!
   * \brief BeginReading  Начать чтение файла отгрузки
   */
  void BeginReading(void *w);
  /*!
   * \brief ReadRecord    Читать одну запись
   * \param r Указатель на объект записи типа Record
   */
  void ReadRecord(st_record<Record> *r);
  /*!
   * \brief ReadRecord    Читать одну запись
   * \param r Указатель на объект записи типа NewRecord
   */
  void ReadRecord(st_record<NewRecord> *r);
  /*!
   * \brief ReadRecord    Читать одну запись
   * \param r Указатель на объект записи типа OldRecord
   */
  void ReadRecord(st_record<OldRecord> *r);

private:
  /*!
   * Массив записей типа Record
   */
  st_record<Record> *recs;
  /*!
   * Массив записей типа NewRecord
   */
  st_record<NewRecord> *newrecs;
  /*!
   * Массив записей типа OldRecord
   */
  st_record<OldRecord> *oldrecs;
  /*!
   * Указатель на объект файла
   */
  QFile *grf_fil;
  /*!
   * Признак наличия ошибки
   */
  bool error_flag;
  /*!
   * Указатель на объект родительского окна
   */
  void *parent_wdg_ptr;
  /*!
   * Указатель на буфер файла в памяти
   */
  QByteArray *memfile;
  /*!
   * Указатель на объект потокового ввода/вывода
   */
  QDataStream *stream;
  /*!
   * Количество записей
   */
  quint16 record_count;
  /*!
   * Тип записей
   */
  quint16 records_type;
  /*!
   * Указатель на объект кодировки Windows-1251.
   * Используется для преобразования в Unicode.
   */
  QTextCodec *utf_codec;
};

#endif // GRF_READER_H
