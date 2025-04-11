#include "QtBookmarkButtonsView.h"
#include "QtMessageBox.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>

#include "MessageBookmarkBrowse.h"
#include "MessageBookmarkCreate.h"
#include "MessageBookmarkDelete.h"
#include "MessageBookmarkEdit.h"
#include "QtActions.h"
#include "QtSearchBarButton.h"
#include "QtViewWidgetWrapper.h"
#include "ResourcePaths.h"
#include "utilityQt.h"

QtBookmarkButtonsView::QtBookmarkButtonsView(ViewLayout* viewLayout)
	: BookmarkButtonsView(viewLayout) 
{
	m_widget = new QFrame();
	m_widget->setObjectName(QStringLiteral("bookmark_bar"));

	QBoxLayout* layout = new QHBoxLayout();
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setAlignment(Qt::AlignTop);
	m_widget->setLayout(layout);

	m_createBookmarkButton = new QtSearchBarButton(ResourcePaths::getGuiDirectoryPath().concatenate(L"bookmark_view/images/edit_bookmark_icon.png"));
	m_createBookmarkButton->setObjectName(QStringLiteral("bookmark_button"));
	m_createBookmarkButton->setToolTip(QtActions::bookmarkActiveSymbol().tooltip());
	m_createBookmarkButton->setEnabled(false);
	layout->addWidget(m_createBookmarkButton);

	connect(m_createBookmarkButton, &QPushButton::clicked, this, &QtBookmarkButtonsView::createBookmarkClicked);

	m_showBookmarksButton = new QtSearchBarButton(ResourcePaths::getGuiDirectoryPath().concatenate(L"bookmark_view/images/bookmark_list_icon.png"));
	m_showBookmarksButton->setObjectName(QStringLiteral("show_bookmark_button"));
	m_showBookmarksButton->setToolTip(QtActions::bookmarkManager().tooltip());
	layout->addWidget(m_showBookmarksButton);

	connect(m_showBookmarksButton, &QPushButton::clicked, this, &QtBookmarkButtonsView::showBookmarksClicked);
}

void QtBookmarkButtonsView::createWidgetWrapper()
{
	setWidgetWrapper(std::make_shared<QtViewWidgetWrapper>(m_widget));
}

void QtBookmarkButtonsView::refreshView()
{
	m_onQtThread([=, this]() {
		m_widget->setStyleSheet(utility::getStyleSheet(ResourcePaths::getGuiDirectoryPath().concatenate(
														   L"bookmark_view/bookmark_view.css"))
									.c_str());
	});
}

void QtBookmarkButtonsView::setCreateButtonState(const MessageBookmarkButtonState::ButtonState& state)
{
	m_onQtThread([=, this]() {
		m_createButtonState = state;

		m_createBookmarkButton->setIconPath(ResourcePaths::getGuiDirectoryPath().concatenate(
			L"bookmark_view/images/edit_bookmark_icon.png"));

		if (state == MessageBookmarkButtonState::CAN_CREATE)
		{
			m_createBookmarkButton->setEnabled(true);
		}
		else if (state == MessageBookmarkButtonState::CANNOT_CREATE)
		{
			m_createBookmarkButton->setEnabled(false);
		}
		else if (state == MessageBookmarkButtonState::ALREADY_CREATED)
		{
			m_createBookmarkButton->setEnabled(true);

			m_createBookmarkButton->setIconPath(ResourcePaths::getGuiDirectoryPath().concatenate(
				L"bookmark_view/images/bookmark_active.png"));
		}
		else
		{
			m_createBookmarkButton->setEnabled(false);
		}
	});
}

void QtBookmarkButtonsView::createBookmarkClicked()
{
	if (m_createButtonState == MessageBookmarkButtonState::CAN_CREATE)
	{
		MessageBookmarkCreate().dispatch();
	}
	else if (m_createButtonState == MessageBookmarkButtonState::ALREADY_CREATED)
	{
		QtMessageBox msgBox;
		msgBox.setText(tr("Edit Bookmark"));
		msgBox.setInformativeText(tr("Do you want to edit or delete the bookmark for this symbol?"));
		QPushButton *editButton = msgBox.addButton(tr("Edit"), QtMessageBox::ButtonRole::YesRole);
		QPushButton *deleteButton = msgBox.addButton(tr("Delete"), QtMessageBox::ButtonRole::NoRole);
		QPushButton* cancelButton = msgBox.addButton(tr("Cancel"), QtMessageBox::ButtonRole::RejectRole);
		msgBox.setDefaultButton(cancelButton);
		msgBox.setIcon(QtMessageBox::Icon::Question);

		QAbstractButton *clickedButton = msgBox.execModal();
		if (clickedButton == editButton)
		{
			MessageBookmarkEdit().dispatch();
		}
		else if (clickedButton == deleteButton)
		{
			MessageBookmarkDelete().dispatch();
		}
	}
}

void QtBookmarkButtonsView::showBookmarksClicked()
{
	MessageBookmarkBrowse().dispatch();
}
