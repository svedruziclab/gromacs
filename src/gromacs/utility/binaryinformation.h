/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team.
 * Copyright (c) 2013,2014,2015,2017,2018, by the GROMACS development team, led by
 * Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
 * and including many others, as listed in the AUTHORS file in the
 * top-level source directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */
/*! \libinternal \file
 * \brief Helper functionality for information about the currently running binary
 *
 * \inlibraryapi
 * \ingroup module_utility
 */
#ifndef GMX_UTILITY_BINARYINFORMATION_H
#define GMX_UTILITY_BINARYINFORMATION_H

#include <cstdio>

namespace gmx
{

class IProgramContext;
class TextWriter;

/*! \libinternal \brief
 * Settings for printBinaryInformation().
 *
 * This class is used to specify what printBinaryInformation() prints.
 *
 * \ingroup module_utility
 * \inlibraryapi
 */
class BinaryInformationSettings
{
    public:
        BinaryInformationSettings();

        //! Set whether to print information about build settings.
        BinaryInformationSettings &extendedInfo(bool bEnabled)
        {
            bExtendedInfo_ = bEnabled;
            return *this;
        }
        //! Set whether to print copyright and license information.
        BinaryInformationSettings &copyright(bool bEnabled)
        {
            bCopyright_ = bEnabled;
            return *this;
        }
        //! Set whether to print the process ID.
        BinaryInformationSettings &processId(bool bEnabled)
        {
            bProcessId_ = bEnabled;
            return *this;
        }
        //! Set whether to print a header line with "Generated by" text (for output files).
        BinaryInformationSettings &generatedByHeader(bool bEnabled)
        {
            bGeneratedByHeader_ = bEnabled;
            return *this;
        }
        //! Prefix each line with this string.
        BinaryInformationSettings &linePrefix(const char *prefix)
        {
            prefix_ = prefix;
            return *this;
        }
        //! Suffix each line with this string.
        BinaryInformationSettings &lineSuffix(const char *suffix)
        {
            suffix_ = suffix;
            return *this;
        }

    private:
        bool        bExtendedInfo_;
        bool        bCopyright_;
        bool        bProcessId_;
        bool        bGeneratedByHeader_;
        const char *prefix_;
        const char *suffix_;

        //! Needed to read the members without otherwise unnecessary accessors.
        friend void printBinaryInformation(
            TextWriter                      *writer,
            const IProgramContext           &programContext,
            const BinaryInformationSettings &settings);
};

/*! \brief
 * Print basic information about the executable.
 *
 * \param     fp             Where to print the information to.
 * \param[in] programContext Program information object to use.
 */
void printBinaryInformation(FILE                          *fp,
                            const IProgramContext         &programContext);
/*! \brief
 * Print basic information about the executable with custom settings.
 *
 * \param     fp             Where to print the information to.
 * \param[in] programContext Program information object to use.
 * \param[in] settings       Specifies what to print.
 *
 * \see BinaryInformationSettings
 */
void printBinaryInformation(FILE                            *fp,
                            const IProgramContext           &programContext,
                            const BinaryInformationSettings &settings);

/*! \brief
 * Print basic information about the executable with custom settings.
 *
 * \param[out] writer         Where to print the information.
 * \param[in]  programContext Program information object to use.
 * \param[in]  settings       Specifies what to print.
 * \throws     std::bad_alloc if out of memory.
 *
 * \see BinaryInformationSettings
 */
void printBinaryInformation(TextWriter                      *writer,
                            const IProgramContext           &programContext,
                            const BinaryInformationSettings &settings);

}     // namespace gmx

#endif
