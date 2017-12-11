#ifndef QTAR_H
#define QTAR_H

#include "../qarchive.h"

namespace Archive {
namespace Tar {

class QTar : public QArchive
{
	Q_OBJECT
public:
	QTar(const QString& archive="");
	~QTar();

	bool isEndBuff(const char*);
	Error extract(const QString& archive,const QString& dir=".");
	Error extract();
	bool verifyChecksum(const char*);
	uint unpackedSize();

};
}

}

#endif // QTAR_H
