/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmCursesBoolWidget.h"

#include "cmCursesWidget.h"
#include "cmState.h"

#include <string>

cmCursesBoolWidget::cmCursesBoolWidget(int width, int height, int left,
                                       int top)
  : cmCursesWidget(width, height, left, top)
{
  this->Type = cmState::BOOL;
  set_field_fore(this->Field, A_NORMAL);
  set_field_back(this->Field, A_STANDOUT);
  field_opts_off(this->Field, O_STATIC);
  this->SetValueAsBool(false);
}

bool cmCursesBoolWidget::HandleInput(int& key, cmCursesMainForm* /*fm*/,
                                     WINDOW* w)
{

  // toggle boolean values with enter or space
  // 10 == enter
  if (key == 10 || key == KEY_ENTER || key == ' ') {
    if (this->GetValueAsBool()) {
      this->SetValueAsBool(false);
    } else {
      this->SetValueAsBool(true);
    }

    touchwin(w);
    wrefresh(w);
    return true;
  }
  return false;
}

void cmCursesBoolWidget::SetValueAsBool(bool value)
{
  if (value) {
    this->SetValue("ON");
  } else {
    this->SetValue("OFF");
  }
}

bool cmCursesBoolWidget::GetValueAsBool()
{
  return this->Value == "ON";
}
