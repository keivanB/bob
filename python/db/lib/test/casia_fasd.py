#!/usr/bin/env python
# vim: set fileencoding=utf-8 :
#Ivana Chingovska <ivana.chingovska@idiap.ch>
#Tue Mar  6 11:26:33 CET 2012
#
# Copyright (C) 2011-2012 Idiap Research Institute, Martigny, Switzerland
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

"""A few checks at the CASIA_FASD database.
"""

import os, sys
import unittest
import bob

class FASDDatabaseTest(unittest.TestCase):
  """Performs various tests on the CASIA_FASD spoofing attack database."""


  def test01_query(self):
    db = bob.db.casia_fasd.Database()
    
    f = db.files()
    self.assertEqual(len(set(f.values())), 600) # number of all the videos in the database

    f = db.files(groups='train', ids=[21])
    self.assertEqual(len(set(f.values())), 0) # number of train videos for client 21
   
    f = db.files(groups='test', cls='real')
    self.assertEqual(len(set(f.values())), 90) # number of real test videos (30 clients * 3 qualitites)
    
    f = db.files(groups='test', cls='real', types='cut')
    self.assertEqual(len(set(f.values())), 0) # number of real test videos - cut attacks (can not be real and attacks at the same time of course)

    f = db.files(groups='train', cls='real', qualities='low')
    self.assertEqual(len(set(f.values())), 20) # number of real train videos with low quality (20 clients * 1 real low quality video)

    f = db.files(groups='train', cls='attack', qualities='normal')
    self.assertEqual(len(set(f.values())), 60) # number of real train videos with normal quality (20 clients * 3 attack types)

    f = db.files(groups='test', qualities='high')
    self.assertEqual(len(set(f.values())), 120) # number of real test videos with high quality (30 clients * 4 attack types)
    
    f = db.files(groups='test', types='warped')
    self.assertEqual(len(set(f.values())), 90) # number of test warped videos (30 clients * 3 qualities)

    f = db.files(groups='test', types='video', qualities='high', ids=[1,2,3])
    self.assertEqual(len(set(f.values())), 0) # clients with ids 1, 2 and 3 are not in the test set

    f = db.files(groups='train', types='video', qualities='high', ids=[1,2,3])
    self.assertEqual(len(set(f.values())), 3) # number of high quality video attacks of clients 1, 2 and 3 (3 clients * 1)
   
    f = db.files(directory = 'xxx', extension='.avi', groups='train', types='video', qualities='high', ids=1)
    self.assertEqual(len(set(f.values())), 1) # number of high quality video attacks of client 1(1 client * 1)
    self.assertEqual(f[0], 'xxx/train_release/1/HR_4.avi')

  def test02_cross_valid(self): # testing the cross-validation subsets
    db = bob.db.casia_fasd.Database()
    import pdb; pdb.set_trace()
    db.cross_valid_gen(60, 60, 5) # 60 is the number of real samples as well as in each attack type of the database
    '''
    subsets_real, subsets_attack = db.cross_valid_read()
    self.assertEqual(len(subsets_real), 10)
    self.assertEqual(len(subsets_attack), 10)
    for i in range(0,10):
      self.assertTrue(len(subsets_real[i]) in (174, 175))
      self.assertTrue(len(subsets_attack[i]) in (174, 175))

    import pdb; pdb.set_trace()
    files_real_val, files_real_train = db.cross_valid_foldfiles(version='raw', cls='real', fold_no=1)
    self.assertTrue(len(files_real_val) in (174, 175)) # number of samples in validation subset of real accesses
    self.assertTrue(len(files_real_train) in (1568, 1569)) # number of samples in training subset of real accesses
    files_attack_val, files_attack_train = db.cross_valid_foldfiles(version='detected_face', cls='attack', fold_no=3, directory='aaa', extension='.jpg')
    self.assertTrue(len(files_attack_val) in (174, 175)) # number of samples in validation subset of attacks
    self.assertTrue(len(files_attack_train) in (1573, 1574)) # number of samples in training subset of attacks
    '''
# Instantiates our standard main module for unittests
main = bob.helper.unittest_main(FASDDatabaseTest)
