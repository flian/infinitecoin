// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("infinitecoin://iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("infinitecoin:iAu4xQfh23eCjxvtimmdb8EXMLj4LXmDce?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
