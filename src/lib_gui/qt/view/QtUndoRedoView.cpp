#include "QtUndoRedoView.h"

#include "utilityQt.h"
#include "QtViewWidgetWrapper.h"
#include "QtResources.h"

using namespace utility;

QtUndoRedoView::QtUndoRedoView(ViewLayout *viewLayout)
	: UndoRedoView(viewLayout)
{
	m_widget = new QtUndoRedo();
}

void QtUndoRedoView::createWidgetWrapper()
{
	setWidgetWrapper(std::make_shared<QtViewWidgetWrapper>(m_widget));
}

void QtUndoRedoView::refreshView()
{
	m_onQtThread([=, this]()
	{
		m_widget->setStyleSheet(QtResources::loadStyleSheet(QtResources::UNDOREDO_VIEW_CSS));
	});
}

void QtUndoRedoView::setRedoButtonEnabled(bool enabled)
{
	m_onQtThread([=, this]()
	{
		m_widget->setRedoButtonEnabled(enabled);
	});
}

void QtUndoRedoView::setUndoButtonEnabled(bool enabled)
{
	m_onQtThread([=, this]()
	{
		m_widget->setUndoButtonEnabled(enabled);
	});
}

void QtUndoRedoView::updateHistory(const std::vector<SearchMatch> &searchMatches, size_t currentIndex)
{
	m_onQtThread([=, this]()
	{
		m_widget->updateHistory(searchMatches, currentIndex);
	});
}
