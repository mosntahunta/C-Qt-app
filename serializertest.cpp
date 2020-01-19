#include "listmodel.h"
#include "serializer.h"

#include "serializertest.h"

QTEST_MAIN(SerializerTest)
//#include "serializertest.moc"

void
SerializerTest::Hello()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}
