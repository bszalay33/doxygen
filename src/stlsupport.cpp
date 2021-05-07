/******************************************************************************
 *
 * Copyright (C) 1997-2019 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby
 * granted. No representations are made about the suitability of this software
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#include "stlsupport.h"
#include "entry.h"
#include "config.h"
#include "util.h"

/** A struct contained the data for an STL class */
struct STLInfo
{
  const CppIdentifier className;
  const char *baseClass1;
  const char *baseClass2;
  const char *templType1;
  const char *templName1;
  const char *templType2;
  const char *templName2;
  bool virtualInheritance;
  bool iterators;
};

static STLInfo g_stlinfo[] =
{
  // className                             baseClass1                      baseClass2             templType1     templName1     templType2    templName2     virtInheritance  // iterators
  { (CppIdentifier)"allocator",            0,                              0,                     "T",           "elements",    0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"auto_ptr",             0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // deprecated
  { (CppIdentifier)"smart_ptr",            0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"unique_ptr",           0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"shared_ptr",           0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++14
  { (CppIdentifier)"weak_ptr",             0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"atomic",               0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"atomic_ref",           0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++20
  { (CppIdentifier)"lock_guard",           0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"unique_lock",          0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"shared_lock",          0,                              0,                     "T",           "ptr",         0,            0,             FALSE,              FALSE }, // C++14
  { (CppIdentifier)"ios_base",             0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"error_code",           0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"error_category",       0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"system_error",         0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"error_condition",      0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"thread",               0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"jthread",              0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"mutex",                0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"timed_mutex",          0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"recursive_mutex",      0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"recursive_timed_mutex",0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++11
  { (CppIdentifier)"shared_mutex",         0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++17
  { (CppIdentifier)"shared_timed_mutex",   0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }, // C++14
  { (CppIdentifier)"basic_ios",            "ios_base",                     0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_istream",        "basic_ios<Char>",              0,                     "Char",        0,             0,            0,             TRUE,               FALSE },
  { (CppIdentifier)"basic_ostream",        "basic_ios<Char>",              0,                     "Char",        0,             0,            0,             TRUE,               FALSE },
  { (CppIdentifier)"basic_iostream",       "basic_istream<Char>",          "basic_ostream<Char>", "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_ifstream",       "basic_istream<Char>",          0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_ofstream",       "basic_ostream<Char>",          0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_fstream",        "basic_iostream<Char>",         0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_istringstream",  "basic_istream<Char>",          0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_ostringstream",  "basic_ostream<Char>",          0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_stringstream",   "basic_iostream<Char>",         0,                     "Char",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ios",                  "basic_ios<char>",              0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wios",                 "basic_ios<wchar_t>",           0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"istream",              "basic_istream<char>",          0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wistream",             "basic_istream<wchar_t>",       0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ostream",              "basic_ostream<char>",          0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wostream",             "basic_ostream<wchar_t>",       0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ifstream",             "basic_ifstream<char>",         0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wifstream",            "basic_ifstream<wchar_t>",      0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ofstream",             "basic_ofstream<char>",         0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wofstream",            "basic_ofstream<wchar_t>",      0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"fstream",              "basic_fstream<char>",          0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wfstream",             "basic_fstream<wchar_t>",       0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"istringstream",        "basic_istringstream<char>",    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wistringstream",       "basic_istringstream<wchar_t>", 0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ostringstream",        "basic_ostringstream<char>",    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wostringstream",       "basic_ostringstream<wchar_t>", 0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"stringstream",         "basic_stringstream<char>",     0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"wstringstream",        "basic_stringstream<wchar_t>",  0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"basic_string",         0,                              0,                     "Char",        0,             0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"string",               "basic_string<char>",           0,                     0,             0,             0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"wstring",              "basic_string<wchar_t>",        0,                     0,             0,             0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"u8string",             "basic_string<char8_t>",        0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++20
  { (CppIdentifier)"u16string",            "basic_string<char16_t>",       0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"u32string",            "basic_string<char32_t>",       0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"basic_string_view",    0,                              0,                     "Char",        0,             0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"string_view",          "basic_string_view<char>",      0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++17
  { (CppIdentifier)"wstring_view",         "basic_string_view<wchar_t>",   0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++17
  { (CppIdentifier)"u8string_view",        "basic_string_view<char8_t>",   0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++20
  { (CppIdentifier)"u16string_view",       "basic_string_view<char16_t>",  0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++17
  { (CppIdentifier)"u32string_view",       "basic_string_view<char32_t>",  0,                     0,             0,             0,            0,             FALSE,              TRUE  }, // C++17
  { (CppIdentifier)"complex",              0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"bitset",               0,                              0,                     "Bits",        0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"deque",                0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"list",                 0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"forward_list",         0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"map",                  0,                              0,                     "K",           "keys",        "T",          "elements",    FALSE,              TRUE  },
  { (CppIdentifier)"unordered_map",        0,                              0,                     "K",           "keys",        "T",          "elements",    FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"multimap",             0,                              0,                     "K",           "keys",        "T",          "elements",    FALSE,              TRUE  },
  { (CppIdentifier)"unordered_multimap",   0,                              0,                     "K",           "keys",        "T",          "elements",    FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"set",                  0,                              0,                     "K",           "keys",        0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"unordered_set",        0,                              0,                     "K",           "keys",        0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"multiset",             0,                              0,                     "K",           "keys",        0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"unordered_multiset",   0,                              0,                     "K",           "keys",        0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"array",                0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  }, // C++11
  { (CppIdentifier)"vector",               0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  },
  { (CppIdentifier)"span",                 0,                              0,                     "T",           "elements",    0,            0,             FALSE,              TRUE  }, // C++20
  { (CppIdentifier)"queue",                0,                              0,                     "T",           "elements",    0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"priority_queue",       0,                              0,                     "T",           "elements",    0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"stack",                0,                              0,                     "T",           "elements",    0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"valarray",             0,                              0,                     "T",           "elements",    0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"exception",            0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"bad_alloc",            "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"bad_cast",             "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"bad_typeid",           "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"logic_error",          "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"ios_base::failure",    "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"runtime_error",        "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"bad_exception",        "exception",                    0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"domain_error",         "logic_error",                  0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"invalid_argument",     "logic_error",                  0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"length_error",         "logic_error",                  0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"out_of_range",         "logic_error",                  0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"range_error",          "runtime_error",                0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"overflow_error",       "runtime_error",                0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)"underflow_error",      "runtime_error",                0,                     0,             0,             0,            0,             FALSE,              FALSE },
  { (CppIdentifier)0,                      0,                              0,                     0,             0,             0,            0,             FALSE,              FALSE }
};

static void addSTLMember(const std::shared_ptr<Entry> &root,const char *type,const char *name)
{
  std::shared_ptr<Entry> memEntry = std::make_shared<Entry>();
  memEntry->name       = name;
  memEntry->type       = type;
  memEntry->protection = Public;
  memEntry->section    = Entry::VARIABLE_SEC;
  memEntry->brief      = "STL member";
  memEntry->hidden     = FALSE;
  memEntry->artificial = TRUE;
  root->moveToSubEntryAndKeep(memEntry);
}

static void addSTLIterator(const std::shared_ptr<Entry> &classEntry,const char *name)
{
  std::shared_ptr<Entry> iteratorClassEntry = std::make_shared<Entry>();
  iteratorClassEntry->fileName  = "[STL]";
  iteratorClassEntry->startLine = 1;
  iteratorClassEntry->name      = name;
  iteratorClassEntry->section   = Entry::CLASS_SEC;
  iteratorClassEntry->brief     = "STL iterator class";
  iteratorClassEntry->hidden    = FALSE;
  iteratorClassEntry->artificial= TRUE;
  classEntry->moveToSubEntryAndKeep(iteratorClassEntry);
}

static void addSTLClass(const std::shared_ptr<Entry> &root,const STLInfo *info)
{
  //printf("Adding STL class %s\n",info->className);
  QCString fullName = info->className.get();
  fullName.prepend("std::");

  // add fake Entry for the class
  std::shared_ptr<Entry> classEntry = std::make_shared<Entry>();
  classEntry->fileName  = "[STL]";
  classEntry->startLine = 1;
  classEntry->name      = fullName;
  classEntry->section   = Entry::CLASS_SEC;
  classEntry->brief     = "STL class";
  classEntry->hidden    = FALSE;
  classEntry->artificial= TRUE;

  // add template arguments to class
  if (info->templType1)
  {
    ArgumentList al;
    Argument a;
    a.type="typename";
    a.name=info->templType1;
    al.push_back(a);
    if (info->templType2) // another template argument
    {
      a.type="typename";
      a.name=info->templType2;
      al.push_back(a);
    }
    classEntry->tArgLists.push_back(al);
  }
  // add member variables
  if (info->templName1)
  {
    addSTLMember(classEntry,info->templType1,info->templName1);
  }
  if (info->templName2)
  {
    addSTLMember(classEntry,info->templType2,info->templName2);
  }
  if (fullName=="std::auto_ptr" ||
      fullName=="std::smart_ptr" ||
      fullName=="std::shared_ptr" ||
      fullName=="std::weak_ptr" ||
      fullName=="std::unique_ptr")
  {
    std::shared_ptr<Entry> memEntry = std::make_shared<Entry>();
    memEntry->name       = "operator->";
    memEntry->args       = "()";
    memEntry->type       = "T*";
    memEntry->protection = Public;
    memEntry->section    = Entry::FUNCTION_SEC;
    memEntry->brief      = "STL member";
    memEntry->hidden     = FALSE;
    memEntry->artificial = FALSE;
    classEntry->moveToSubEntryAndKeep(memEntry);
  }
  if (info->baseClass1)
  {
    classEntry->extends.push_back(BaseInfo(info->baseClass1,Public,info->virtualInheritance?Virtual:Normal));
  }
  if (info->baseClass2)
  {
    classEntry->extends.push_back(BaseInfo(info->baseClass2,Public,info->virtualInheritance?Virtual:Normal));
  }
  if (info->iterators)
  {
    // add iterator class
    addSTLIterator(classEntry,fullName+"::iterator");
    addSTLIterator(classEntry,fullName+"::const_iterator");
    addSTLIterator(classEntry,fullName+"::reverse_iterator");
    addSTLIterator(classEntry,fullName+"::const_reverse_iterator");
  }
  root->moveToSubEntryAndKeep(classEntry);
}


static void addSTLClasses(const std::shared_ptr<Entry> &root)
{
  std::shared_ptr<Entry> namespaceEntry = std::make_shared<Entry>();
  namespaceEntry->fileName  = "[STL]";
  namespaceEntry->startLine = 1;
  namespaceEntry->name      = "std";
  namespaceEntry->section   = Entry::NAMESPACE_SEC;
  namespaceEntry->brief     = "STL namespace";
  namespaceEntry->hidden    = FALSE;
  namespaceEntry->artificial= TRUE;

  STLInfo *info = g_stlinfo;
  while (info->className.get())
  {
    addSTLClass(namespaceEntry,info);
    info++;
  }

  root->moveToSubEntryAndKeep(namespaceEntry);
}

void addSTLSupport(std::shared_ptr<Entry> &root)
{
  if (Config_getBool(BUILTIN_STL_SUPPORT))
  {
    addSTLClasses(root);
  }
}
