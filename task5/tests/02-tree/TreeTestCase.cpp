//
// Created by akhtyamovpavel on 5/1/20.
//

#include <boost/filesystem.hpp>

#include "TreeTestCase.h"
#include "Tree.h"

using boost::filesystem::create_directory;
using boost::filesystem::ofstream;
using boost::filesystem::rename;
using boost::filesystem::remove_all;
using boost::filesystem::path;

void TreeTest::SetUp() {
  // Creating following filesystem structure:
  // - TreeTestDir
  //   - SubDir
  //   - File

  create_directory("TreeTestDir");

  create_directory("TreeTestDir/SubDir");

  ofstream("TreeTestDir/FileCreate");
  rename("TreeTestDir/FileCreate", "TreeTestDir/File");
}

void TreeTest::TearDown() {
  remove_all("TreeTestDir");
}

TEST_F(TreeTest, NotExistingFile) {
  ASSERT_THROW(GetTree("TreeTestDir/NotExistingFile", true), std::invalid_argument);
}

TEST_F(TreeTest, NotDirectoryFile) {
  ASSERT_THROW(GetTree("TreeTestDir/File", true), std::invalid_argument);
}

TEST_F(TreeTest, TestEmptyFolder) {
  auto file_node_list = GetTree("TreeTestDir/SubDir", true);
  EXPECT_EQ(file_node_list.children.size(), 0);
  EXPECT_EQ(file_node_list, FileNode({"SubDir",true, std::vector<FileNode>()}));
}

TEST_F(TreeTest, TestNotEmptyFolderOnlyDir) {
  auto file_node_list = GetTree("TreeTestDir", true);
  EXPECT_EQ(file_node_list.children.size(), 1);
  EXPECT_EQ(file_node_list.children[0], FileNode({"SubDir",true, std::vector<FileNode>()}));
}

TEST_F(TreeTest, TestNotEmptyFolderNotOnlyDir) {
  auto file_node_list = GetTree("TreeTestDir", false);
  EXPECT_EQ(file_node_list.children.size(), 2);
}
