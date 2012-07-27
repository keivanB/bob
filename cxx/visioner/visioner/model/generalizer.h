/**
 * @file visioner/visioner/model/generalizer.h
 * @date Fri 27 Jul 13:58:57 2012 CEST
 * @author Andre Anjos <andre.anjos@idiap.ch>
 *
 * @brief This file was part of Visioner and originally authored by "Cosmin
 * Atanasoaei <cosmin.atanasoaei@idiap.ch>". It was only modified to conform to
 * Bob coding standards and structure.
 *
 * Copyright (C) 2011-2012 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOB_VISIONER_GENERALIZER_H
#define BOB_VISIONER_GENERALIZER_H

#include "visioner/model/ml.h"

namespace bob { namespace visioner {

  ////////////////////////////////////////////////////////////////////////////////
  // Selects from a set of models the one that generalizes 
  //	the best on the validation dataset.
  ////////////////////////////////////////////////////////////////////////////////

  template <class TModel>
    class Generalizer
    {
      public:	

        // Constructor
        Generalizer() :	m_train_error(0.0), m_valid_error(0.0)
      {
      }

        // Clear history
        void clear()
        {
          m_train_errors.clear();
          m_valid_errors.clear();
        }

        // Process a new model with the given training and validation loss values
        //	(discard <model> if it is overfitting)
        bool process(scalar_t train_error, scalar_t valid_error,
            const TModel& model, const string_t& description)
        {
          bool better = false;

          // Is <model> the best so far?!
          if (m_valid_errors.empty() ||
              valid_error < *std::min_element(m_valid_errors.begin(), m_valid_errors.end()))
          {
            m_model = model;
            m_description = description;
            m_train_error = train_error;
            m_valid_error = valid_error;
            better = true;
          }

          m_train_errors.push_back(train_error);
          m_valid_errors.push_back(valid_error);

          return better;
        }

        // Access functions		
        const TModel& model() const { return m_model; }
        const string_t& description() const { return m_description; }
        scalar_t train_error() const { return m_train_error; }
        scalar_t valid_error() const { return m_valid_error; }
        scalar_t last_train_error() const { return last(m_train_errors); }
        scalar_t last_valid_error() const { return last(m_valid_errors); }

      private:

        // Returns the last entry in a list of values (if any)
        static scalar_t last(const scalars_t& values)
        {
          return values.empty() ? 
            std::numeric_limits<scalar_t>::max() : 
            *values.rbegin();
        }

        // Attributes
        scalars_t	m_train_errors;
        scalars_t	m_valid_errors;
        string_t	m_description;	// Description of the optimal parameters
        scalar_t	m_train_error;	// Optimal train loss
        scalar_t	m_valid_error;	// Optimal validation loss
        TModel		m_model;	// Optimal model
    };

}}

#endif // BOB_VISIONER_GENERALIZER_H
