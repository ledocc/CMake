/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2004-2009 Kitware, Inc.
  Copyright 2004 Alexander Neundorf (neundorf@kde.org)

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmExtraSublimeTextGenerator_h
#define cmExtraSublimeTextGenerator_h

#include <cmConfigure.h>

#include "cmExternalMakefileProjectGenerator.h"

#include <map>
#include <string>
#include <vector>

class cmGeneratedFileStream;
class cmGeneratorTarget;
class cmLocalGenerator;
class cmMakefile;
class cmSourceFile;

/** \class cmExtraSublimeTextGenerator
 * \brief Write Sublime Text 2 project files for Makefile based projects
 */
class cmExtraSublimeTextGenerator : public cmExternalMakefileProjectGenerator
{
public:
  static cmExternalMakefileProjectGeneratorFactory* GetFactory();
  typedef std::map<std::string, std::vector<std::string> > MapSourceFileFlags;
  cmExtraSublimeTextGenerator();

  void Generate() CM_OVERRIDE;

private:
  void CreateProjectFile(const std::vector<cmLocalGenerator*>& lgs);

  void CreateNewProjectFile(const std::vector<cmLocalGenerator*>& lgs,
                            const std::string& filename);

  /** Appends all targets as build systems to the project file and get all
   * include directories and compiler definitions used.
   */
  void AppendAllTargets(const std::vector<cmLocalGenerator*>& lgs,
                        const cmMakefile* mf, cmGeneratedFileStream& fout,
                        MapSourceFileFlags& sourceFileFlags);
  /** Returns the build command that needs to be executed to build the
   *  specified target.
   */
  std::string BuildMakeCommand(const std::string& make, const char* makefile,
                               const std::string& target);
  /** Appends the specified target to the generated project file as a Sublime
   *  Text build system.
   */
  void AppendTarget(cmGeneratedFileStream& fout, const std::string& targetName,
                    cmLocalGenerator* lg, cmGeneratorTarget* target,
                    const char* make, const cmMakefile* makefile,
                    const char* compiler, MapSourceFileFlags& sourceFileFlags,
                    bool firstTarget);
  /**
   * Compute the flags for compilation of object files for a given @a language.
   * @note Generally it is the value of the variable whose name is computed
   *       by LanguageFlagsVarName().
   */
  std::string ComputeFlagsForObject(cmSourceFile* source, cmLocalGenerator* lg,
                                    cmGeneratorTarget* gtgt);

  std::string ComputeDefines(cmSourceFile* source, cmLocalGenerator* lg,
                             cmGeneratorTarget* gtgt);
};

#endif
