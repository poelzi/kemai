#pragma once

#include <QAbstractListModel>

namespace kemai {

class KimaiDataListModel : public QAbstractListModel
{
public:
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    template<class K> void setKimaiData(const std::vector<K>& kds)
    {
        beginResetModel();
        if (!kds.empty())
        {
            mData = {{"", 0}};
            for (const auto& kd : kds)
            {
                mData.emplace(kd.name, kd.id);
            }
        }
        endResetModel();
    }

private:
    std::map<QString, int> mData;
};

} // namespace kemai
