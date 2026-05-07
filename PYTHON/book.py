books = []  
def show_menu():
    print("1. 添加图书")
    print("2. 删除图书")
    print("3. 查看所有图书")
    print("4. 修改图书信息")
    print("5. 查找图书")
    print("6. 退出系统")
def add_book():
    book_id = input("请输入图书编号：")
    for book in books:
        if book["编号"] == book_id:
            print("添加失败：该编号已经存在！")
            return
    name = input("请输入图书名称：")
    author = input("请输入作者：")
    price = input("请输入价格：")
    book = {
        "编号": book_id,
        "书名": name,
        "作者": author,
        "价格": price
    }
    books.append(book)
    print("图书添加成功！")
def delete_book():
    book_id = input("请输入要删除的图书编号：")
    for book in books:
        if book["编号"] == book_id:
            books.remove(book)
            print("图书删除成功！")
            return
    print("删除失败：没有找到该编号的图书。")
def show_books():
    if len(books) == 0:
        print("当前没有图书信息。")
        return
    print("\n========== 所有图书信息 ==========")
    for book in books:
        print(f"编号：{book['编号']} | 书名：{book['书名']} | 作者：{book['作者']} | 价格：{book['价格']}")

def update_book():
    book_id = input("请输入要修改的图书编号：")

    for book in books:
        if book["编号"] == book_id:
            print("找到图书，请输入新的信息。")
            new_name = input("请输入新的书名：")
            new_author = input("请输入新的作者：")
            new_price = input("请输入新的价格：")
            book["书名"] = new_name
            book["作者"] = new_author
            book["价格"] = new_price
            print("图书信息修改成功！")
            return
    print("修改失败：没有找到该编号的图书。")
def search_book():
    book_id = input("请输入要查找的图书编号：")
    for book in books:
        if book["编号"] == book_id:
            print("\n找到图书：")
            print(f"编号：{book['编号']}")
            print(f"书名：{book['书名']}")
            print(f"作者：{book['作者']}")
            print(f"价格：{book['价格']}")
            return
    print("查找失败：没有找到该编号的图书。")
def main():
    while True:
        show_menu()
        choice = input("请选择功能编号：")
        if choice == "1":
            add_book()
        elif choice == "2":
            delete_book()
        elif choice == "3":
            show_books()
        elif choice == "4":
            update_book()
        elif choice == "5":
            search_book()
        elif choice == "6":
            print("感谢使用图书管理系统，再见！")
            break
        else:
            print("输入错误，请输入 1-6 之间的数字。")
if __name__ == "__main__":
    main()