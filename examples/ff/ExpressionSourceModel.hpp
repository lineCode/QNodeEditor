#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include <iostream>

class ExpressionRangeData;

class QWidget;
class QLineEdit;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ExpressionSourceModel
  : public NodeDataModel
{
  Q_OBJECT

public:
  ExpressionSourceModel();

  virtual
  ~ExpressionSourceModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Expression Source"); }

  bool
  captionVisible() const override
  { return true; }

  QString
  name() const override
  { return QStringLiteral("Expression Source"); }

  std::unique_ptr<NodeDataModel>
  clone() const override
  { return std::make_unique<ExpressionSourceModel>(); }

public:

  QJsonObject
  save() const override;

  void
  restore(QJsonObject const &p) override;

public:

  unsigned int
  nPorts(PortType portType) const override;

std::shared_ptr<NodeDataType>  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override
  { }

  QWidget *
  embeddedWidget() override;

private slots:

  void
  onVariableEdited(QString const &string);

  void
  onRangeEdited(QString const &string);


  void
  processChangedData();

private:

  std::vector<double>
  processRangeText(QString const &rangeText) const;

private:

  std::shared_ptr<ExpressionRangeData> _expression;

  QWidget * _widget;

  QLineEdit * _variableEdit;
  QLineEdit * _rangeEdit;
};
