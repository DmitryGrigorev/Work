#include "settings.h"

/*!
 * \brief Settings::Settings
 */

Settings::Settings() { InitSettings(); }

/*!
 * \brief Settings::InitSettings
 */
void Settings::InitSettings() {
  settings = new QSettings("config", QSettings::NativeFormat);
  recent_files = new QStringList();
  recent_count = 0;
}

/*!
 * \brief Settings::LoadRecentFilesList
 * \param action_list
 */
void Settings::LoadRecentFilesList(QList<QAction *> *action_list) {
  recent_count = settings->value("Welding/Recent/Count", 0).toInt();
  QString recent_file_temp = "";
  for (int i = 0; i < recent_count; i++) {
    recent_file_temp =
        settings->value(QString::asprintf("Welding/Recent/File_%d", i), "")
            .toString();
    if (recent_file_temp.length() > 0) {
      *recent_files << recent_file_temp;
      action_list->append(new QAction(recent_file_temp));
    }
  }
}

/*!
 * \brief Settings::AddNextFileName
 * \param file_name
 */
void Settings::AddNextFileName(QString &file_name) {
  *recent_files << file_name;
  SaveRecentFilesList();
  recent_count++;
  settings->setValue("Welding/Recent/Count", recent_count);
}
/*!
 * \brief Settings::SaveRecentFilesList
 */
void Settings::SaveRecentFilesList() {
  for (int i = 0; i < recent_files->count(); i++) {
    settings->setValue(QString::asprintf("Welding/Recent/File_%d", i),
                       recent_files->at(i));
  }
}
