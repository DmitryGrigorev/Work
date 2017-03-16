#ifndef SETTINGS_H
#define SETTINGS_H

#include <QAction>
#include <QSettings>
#include <QStringList>

/*!
 * \brief The Settings class
 */
class Settings {
public:
  /*!
 * \brief Settings
 */
  Settings();
  /*!
   * \brief InitSettings
   */
  void InitSettings();
  /*!
   * \brief LoadRecentFilesList
   * \param action_list
   */
  void LoadRecentFilesList(QList<QAction *> *action_list);
  /*!
   * \brief AddNextFileName
   * \param fil_name
   */
  void AddNextFileName(QString &fil_name);
  /*!
   * \brief SaveRecentFilesList
   */
  void SaveRecentFilesList();

private:
  /*!
   * \brief settings
   */
  QSettings *settings;
  /*!
   * \brief recent_files
   */
  QStringList *recent_files;
  /*!
   * \brief recent_count
   */
  int recent_count;
};

#endif // SETTINGS_H
