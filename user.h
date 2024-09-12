#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>

struct CUserHandling
{


    static QString _current_user;
    static int _current_staffid;
    static QList<QString> _perm_list;
    static QList<QString> _role_list;

    CUserHandling()
    {
        _current_staffid=0;
        _current_user=NULL;
        _perm_list.clear();
        _role_list.clear();

    }

    static void fill_perm_list()
    {
        _perm_list.clear();
        QSqlQuery queryperm("select PermName from Permissions \
                                join StaffPerm on SPPermFK=PermID \
                                join Staff on StaffID=SPStaffFK \
                                where StaffUser='" + _current_user + "'");

        while (queryperm.next())
        {
            QString perm = queryperm.value(0).toString();
            _perm_list.append(perm);
        }

    }

    static bool search_perm_list(QString& search_string)
    {
        if (_perm_list.contains(search_string))
        {
            return true;
        }
        return false;
    }

    static void fill_role_list()
    {
        _role_list.clear();
        QSqlQuery queryrole("select RoleName from Roles \
                                join StaffRoles on SRRolesFK=RoleID \
                                join Staff on StaffID=SRStaffFK \
                                where StaffUser='" + _current_user + "'");

        while (queryrole.next())
        {
            QString role = queryrole.value(0).toString();
            _role_list.append(role);
        }

    }

    static bool search_role_list(QString& search_string)
    {
        if (_role_list.contains(search_string))
        {
            return true;
        }
        return false;
    }

};

//extern CUserHandling UserHandling;

#endif // USER_H
