/*
	Actionaz
	Copyright (C) 2008-2010 Jonathan Mercier-Ganady

	Actionaz is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actionaz is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#ifndef WINDOWCONDITIONDEFINITION_H
#define WINDOWCONDITIONDEFINITION_H

#include "actiondefinition.h"
#include "windowconditioninstance.h"
#include "textparameterdefinition.h"
#include "listparameterdefinition.h"
#include "ifactionparameterdefinition.h"
#include "variableparameterdefinition.h"

namespace ActionTools
{
	class ActionPack;
	class ActionInstance;
}

namespace Actions
{
	class WindowConditionDefinition : public QObject, public ActionTools::ActionDefinition
	{
	   Q_OBJECT

	public:
		explicit WindowConditionDefinition(ActionTools::ActionPack *pack)
		: ActionDefinition(pack)
		{
			ActionTools::TextParameterDefinition *title = new ActionTools::TextParameterDefinition("title", tr("Window title"), this);
			title->setTooltip(tr("The title of the window to find, you can use wildcards like * (any number of characters) or ? (one character) here"));
			addElement(title);

			ActionTools::ListParameterDefinition *condition = new ActionTools::ListParameterDefinition("condition", tr("Condition"), this);
			condition->setTooltip(tr("The condition to wait for"));
			condition->setItems(WindowConditionInstance::conditions);
			condition->setDefaultValue(WindowConditionInstance::conditions.second.at(WindowConditionInstance::Created));
			addElement(condition);

			ActionTools::IfActionParameterDefinition *ifTrue = new ActionTools::IfActionParameterDefinition("ifTrue", tr("If true"), this);
			ifTrue->setTooltip(tr("What to do if the condition is met"));
			addElement(ifTrue);

			ActionTools::IfActionParameterDefinition *ifFalse = new ActionTools::IfActionParameterDefinition("ifFalse", tr("If false"), this);
			ifFalse->setTooltip(tr("What to do if the condition is not met"));
			addElement(ifFalse);

			ActionTools::VariableParameterDefinition *xCoordinate = new ActionTools::VariableParameterDefinition("xCoordinate", tr("X-coordinate"), this);
			xCoordinate->setTooltip(tr("The x-coordinate of the found window"));
			addElement(xCoordinate, 1);

			ActionTools::VariableParameterDefinition *yCoordinate = new ActionTools::VariableParameterDefinition("yCoordinate", tr("Y-coordinate"), this);
			yCoordinate->setTooltip(tr("The y-coordinate of the found window"));
			addElement(yCoordinate, 1);

			ActionTools::VariableParameterDefinition *width = new ActionTools::VariableParameterDefinition("width", tr("Width"), this);
			width->setTooltip(tr("The width of the found window"));
			addElement(width, 1);

			ActionTools::VariableParameterDefinition *height = new ActionTools::VariableParameterDefinition("height", tr("Height"), this);
			height->setTooltip(tr("The height of the found window"));
			addElement(height, 1);

			ActionTools::VariableParameterDefinition *processId = new ActionTools::VariableParameterDefinition("processId", tr("Process id"), this);
			processId->setTooltip(tr("The process id of the found window"));
			addElement(processId, 1);
		}

		QString name() const													{ return QObject::tr("Window condition"); }
		QString id() const														{ return "ActionWindowCondition"; }
		Flag flags() const														{ return ActionDefinition::flags() | Official; }
		QString description() const												{ return QObject::tr("Checks for the state of a window"); }
		ActionTools::ActionInstance *newActionInstance() const					{ return new WindowConditionInstance(this); }
		Category category() const												{ return Windows; }
		QPixmap icon() const													{ return QPixmap(":/icons/msg.png"); }
		QStringList tabs() const												{ return ActionDefinition::StandardTabs; }

	private:
		Q_DISABLE_COPY(WindowConditionDefinition)
	};
}

#endif // WINDOWCONDITIONDEFINITION_H