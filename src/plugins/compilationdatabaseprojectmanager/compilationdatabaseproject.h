/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <projectexplorer/project.h>
#include <projectexplorer/treescanner.h>
#include <texteditor/texteditor.h>
#include <utils/filesystemwatcher.h>

#include <QFutureWatcher>

namespace CppTools {
class CppProjectUpdater;
}

namespace ProjectExplorer {
class Kit;
}

namespace CompilationDatabaseProjectManager {
namespace Internal {

class CompilationDatabaseProject : public ProjectExplorer::Project
{
    Q_OBJECT

public:
    explicit CompilationDatabaseProject(const Utils::FileName &filename);
    ~CompilationDatabaseProject() override;
    bool needsConfiguration() const override { return false; }
    bool needsBuildConfigurations() const override { return false; }

private:
    RestoreResult fromMap(const QVariantMap &map, QString *errorMessage) override;

    void reparseProject();
    void buildTreeAndProjectParts(const Utils::FileName &projectFile);
    Utils::FileName rootPathFromSettings() const;

    QFutureWatcher<void> m_parserWatcher;
    std::unique_ptr<CppTools::CppProjectUpdater> m_cppCodeModelUpdater;
    std::unique_ptr<ProjectExplorer::Kit> m_kit;
    Utils::FileSystemWatcher m_fileSystemWatcher;
    ProjectExplorer::TreeScanner m_treeScanner;
    QHash<QString, bool> m_mimeBinaryCache;
    bool m_hasTarget = false;
};

class CompilationDatabaseEditorFactory : public TextEditor::TextEditorFactory
{
    Q_OBJECT

public:
    CompilationDatabaseEditorFactory();
};

} // namespace Internal
} // namespace CompilationDatabaseProjectManager
