#ifndef ANDROIDSERVICECONTROL_H
#define ANDROIDSERVICECONTROL_H

#include <QtCore/QLoggingCategory>

#include <QtService/ServiceControl>

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidIntent>
#include <QtAndroidExtras/QAndroidServiceConnection>
#include <QtAndroidExtras/QtAndroid>

class AndroidServiceControl : public QtService::ServiceControl
{
	Q_OBJECT

public:
	explicit AndroidServiceControl(QString &&serviceId, QObject *parent = nullptr);

	QString backend() const override;
	SupportFlags supportFlags() const override;
	bool serviceExists() const override;
	bool isEnabled() const override;
	QVariant callGenericCommand(const QByteArray &kind, const QVariantList &args) override;
	BlockMode blocking() const override;

public Q_SLOTS:
	bool start() override;
	bool stop() override;
	bool setEnabled(bool enabled) override;

protected:
	QString serviceName() const override;

private:
	QByteArray jniServiceId() const;
	QAndroidJniObject serviceComponent() const;
	QAndroidJniObject serviceInfo() const;

	bool bind(QAndroidServiceConnection *serviceConnection, QtAndroid::BindFlags flags);
	void unbind(QAndroidServiceConnection *serviceConnection);
	void startWithIntent(const QAndroidIntent &intent);
};

Q_DECLARE_LOGGING_CATEGORY(logControl)

#endif // ANDROIDSERVICECONTROL_H
