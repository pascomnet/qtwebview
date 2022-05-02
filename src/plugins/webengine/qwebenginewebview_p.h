/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebView module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QWEBENGINEWEBVIEW_P_H
#define QWEBENGINEWEBVIEW_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtGui/qwindow.h>

#include <QtQml/qqmlcomponent.h>

#include <private/qabstractwebview_p.h>
#include <QtWebEngineQuick/QQuickWebEngineProfile>


QT_BEGIN_NAMESPACE

class QQuickWebEngineView;
class QWebEngineLoadingInfo;

class QWebEngineWebViewPrivate : public QAbstractWebView
{
    Q_OBJECT
public:
    explicit QWebEngineWebViewPrivate(QObject *p = nullptr);
    ~QWebEngineWebViewPrivate() override;

    QString httpUserAgent() const override;
    void setHttpUserAgent(const QString &userAgent) override;
    QUrl url() const override;
    void setUrl(const QUrl &url) override;
    bool canGoBack() const override;
    bool canGoForward() const override;
    QString title() const override;
    int loadProgress() const override;
    bool isLoading() const override;

    void setParentView(QObject *parentView) override;
    QObject *parentView() const override;
    void setGeometry(const QRect &geometry) override;
    void setVisibility(QWindow::Visibility visibility) override;
    void setVisible(bool visible) override;
    void setFocus(bool focus) override;

public Q_SLOTS:
    void goBack() override;
    void goForward() override;
    void reload() override;
    void stop() override;
    void loadHtml(const QString &html, const QUrl &baseUrl = QUrl()) override;

private Q_SLOTS:
    void q_urlChanged();
    void q_loadProgressChanged();
    void q_titleChanged();
    void q_loadingChanged(const QWebEngineLoadingInfo &loadRequest);
    void q_profileChanged();
    void q_httpUserAgentChanged();

protected:
    void runJavaScriptPrivate(const QString& script,
                              int callbackId) override;

private:
    QQuickWebEngineProfile *m_profile;
    QString m_httpUserAgent;
    struct QQuickWebEngineViewPtr
    {
        inline QQuickWebEngineView *operator->() const
        {
            if (!m_webEngineView)
                init();
            return m_webEngineView.data();
        }
        void init() const;

        QWebEngineWebViewPrivate *m_parent;
        mutable QScopedPointer<QQuickWebEngineView> m_webEngineView;
    } m_webEngineView;
};

QT_END_NAMESPACE

#endif // QWEBENGINEWEBVIEW_P_H
