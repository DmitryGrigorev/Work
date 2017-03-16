#include "grf_reader.h"
#include "mainwindow.h"

/**
 * @brief GRF_Reader::GRF_Reader
 * @param file_name
 *
 * Создаем объект файла, открываю файл в режиме чтения и записи.
 * Затем загружаю содержимое файла в буфер memfile.
 */
GRF_Reader::GRF_Reader(QString &file_name) {
  utf_codec = QTextCodec::codecForName("Windows-1251");
  memfile = NULL;
  stream = NULL;
  error_flag = false;             //Ошибок нет
  grf_fil = new QFile(file_name); //Создаем объект файла
  if (grf_fil->exists()) {
    grf_fil->open(
        QIODevice::ReadWrite); //Открываем файл в режиме чтения и записи
    memfile = new QByteArray(grf_fil->readAll()); //загружаю файл в память
    stream = new QDataStream(memfile, QIODevice::ReadWrite); //Создаю объект
    //потокового ввода
    //вывода в буфер
    // memfile
    stream->setByteOrder(
        QDataStream::LittleEndian); //Устанавливаю прямой порядок байт в потоке

    *stream >> records_type; //Считываю Тип записей
    *stream >> record_count; //Считываю Количество записей
                             /*
                                                   * Проверяем число записей и тип на корректность
                                                   */
    if (record_count < 1000 &&
        (records_type == RECTYPE || records_type == RECTYPE_NEW ||
         records_type == RECTYPE_OLD)) {
      //((MainWindow *)parent_wdg_ptr)
      //    ->setStatusLabelText(
      //        "Файл отгрузки загружен"); //Выводим текст ошибки в statusbar
    } else {
      error_flag = true;
      //((MainWindow *)parent_wdg_ptr)
      //    ->setStatusLabelText(
      //        "Неизвестный формат файла"); //Выводим текст ошибки в statusbar
    }
  } else {
    error_flag =
        true; //Если файла не существует, то устанавливаем признак ошибки
    //((MainWindow *)parent_wdg_ptr)
    //    ->setStatusLabelText(
    //        "Ошибка чтения файла"); //Выводим текст ошибки в statusbar
    delete grf_fil;
  }
}

/*!
 * \brief GRF_Reader::~GRF_Reader Деструктор класса. Очищает все поля класса.
 */
GRF_Reader::~GRF_Reader() {
  /* Сбрасываю поток ввода/вывода в буфер */
  this->stream->unsetDevice();
  this->stream->resetStatus();
  /* Удаляю указатель на объект потока */
  delete this->stream;
  /* Очищаю буфер файла */
  this->memfile->clear();
  /* Удаляю указатель на буфер */
  delete this->memfile;

  /* Очищаю и удаляю массивы записей, загруженные в память */
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
* @brief GRF_Reader::SetParentWidgetPointer    Установить указатель на объект
* родительского окна
* @param w Указатель
*/
void GRF_Reader::SetParentWidgetPointer(void *w) { this->parent_wdg_ptr = w; }

#include "mainwindow.h"

/*!
 * \brief GRF_Reader::BeginReading
 */
void GRF_Reader::BeginReading(void *w) {
  /*
 *  По типу записей, считанного из файла, выделяем память под определенный
 * массив
 */
  MainWindow *wnd = reinterpret_cast<MainWindow *>(w);
  if (records_type == RECTYPE)
    this->recs = new st_record<Record>[record_count];
  if (records_type == RECTYPE_NEW)
    this->newrecs = new st_record<NewRecord>[record_count];
  if (records_type == RECTYPE_OLD)
    this->oldrecs = new st_record<OldRecord>[record_count];
  /*
   * Цикл считывания записей в массив.
   * По типу записи определяем что и куда надо считывать.
   * После чтения одной записи, выделяю место под массив сорости и тока.
   * Затем считываю массивы.
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
 * Функция считывает одну запись из файла отгрузки
 */
void GRF_Reader::ReadRecord(st_record<Record> *record) {
  record->currency_array = NULL;
  record->r = new Record();
  record->speed_array = NULL;
  // Считываю одну запись
  stream->readRawData((char *)record->r, sizeof(Record));
  // Выделяю место под массивы
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  // Считываю массивы
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
  //Считываю одну запись
  stream->readRawData((char *)record->r, sizeof(NewRecord));
  // Выделяю место под массивы
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  //Считываю массивы
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
  //Считываю одну запись
  stream->readRawData((char *)record->r, sizeof(NewRecord));
  // Выделяю место под массивы
  record->speed_array = new QVector<quint16>(record->r->count);
  record->currency_array = new QVector<quint16>(record->r->count);
  //Считываю массивы
  for (int j = 0; j < 2 * record->r->count; j++) {
    if (j < record->r->count)
      stream->readRawData((char *)&record->currency_array[j], 2);
    else
      stream->readRawData((char *)&record->speed_array[j], 2);
  }
}
