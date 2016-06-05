# lab_sec
# Copyright (C) 2016  Kononov Andrey <flowneee@protonmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

AC_INIT([lab_sec], [2.1])

AC_ARG_WITH([wx],
        [AS_HELP_STRING([--with-wx=PATH], [Full path to wx-config (include executable name)])],
        [wx=$withval],
        [wx=wx-config])
AC_SUBST([wx], [$wx])

AC_ARG_WITH([user],
        [AS_HELP_STRING([--with-user=USER], [Sets user (owner) to run program (default=current user])],
        [user=$withval],
        [user=$(whoami)])
AC_SUBST([user], [$user])

AC_ARG_WITH([group],
        [AS_HELP_STRING([--with-group=GROUP], [Sets group to run program (default=group)])],
        [group=$withval],
        [group=users])
AC_SUBST([group], [$group])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
