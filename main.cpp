#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <string>

namespace Ln {
	typedef std::wstring::size_type LinePos;
	class mark
	{
	public:
		mark();
		mark(const std::wstring& set_marks);
		operator std::wstring();
		const wchar_t escape();
	private:
		std::wstring mrk;
		const wchar_t esc;
	};
/* -------------------------------------------------------------------------------- */
	class headline
	{
	public:
		headline();
		std::wstring get_headline_mark() const;
		bool is_headline(const std::wstring& line);
		size_t mark_pos(const std::wstring& line);
		std::wstring add_html(const std::wstring& line);
	private:
		mark headline_mark;
	};
	class between
	{
	public: 
		enum emphasis{ BOLD=1, ITALIC };
		between();
		bool is_bold(const std::wstring& line);
		bool is_italic(const std::wstring& line);
		int mark_pos(const std::wstring& line, emphasis, LinePos& start, LinePos& end);	
		std::wstring add_boldtag(const std::wstring& line);
		std::wstring add_italictag(const std::wstring& line);
	private:
		mark bold;
		mark italic;
	};
// --------------------------------------------------------------------------------
} /* NameSpace Ln End */
// --------------------------------------------------------------------------------
namespace Ln {
	mark::mark(): esc('\\')
	{ }
	mark::mark(const std::wstring& set_marks): mrk(set_marks), esc('\\')
	{ }
	mark::operator std::wstring()
	{
		return mrk;
	}
	const wchar_t mark::escape()
	{
		return esc;
	}
/* -------------------------------------------------------------------------------- */
	headline::headline(): headline_mark(L"#＃●○■□") 
	{ }
	std::wstring headline::get_headline_mark() const
	{
		return mark(headline_mark);
	}
	bool headline::is_headline(const std::wstring& line)
	{
		if(line.empty()) return false;

		std::wistringstream linebuff(line);
		std::wstring tmp;

		linebuff >> tmp;
		
		mark mark_as;
		if(tmp[0] == mark_as.escape()) return false;

		size_t contain_mark = mark_pos(tmp);
		if(contain_mark == std::wstring::npos) return false;
		if(contain_mark != 0) return false;
		return true;

	}
	size_t headline::mark_pos(const std::wstring& line)
	{
		size_t pos = 0;
		std::wstring hl = get_headline_mark();

		for(LinePos i=0; i<hl.size(); ++i) {
			pos = line.find(hl[i]);
			if(pos != std::wstring::npos) break;
		}		
		return pos;
	}
	std::wstring headline::add_html(const std::wstring& line)
	{
		if(!is_headline(line)) return line;
		
		std::wstring html_headline;
		std::wistringstream linebuff(line);

		linebuff >> html_headline;
		size_t pos = mark_pos(html_headline);
		html_headline.erase(pos, 1);

		return L"<h1>" + html_headline + L"</h1>";
	}
	
	between::between(): bold(L" - "), italic(L" _ ")
	{ }
	bool between::is_bold(const std::wstring& line)
	{
		headline hl;
		if(hl.is_headline(line)) return false;
		
		LinePos start, end;
		mark_pos(line, BOLD, start, end);
		return true;
	}
	bool between::is_italic(const std::wstring& line)
	{
		headline hl;
		if(hl.is_headline(line)) return false;

		LinePos start, end;
		if(mark_pos(line, ITALIC, start, end)) return true;
		return false;
	}
	int between::mark_pos(const std::wstring& line, emphasis mode, LinePos& start, LinePos& end)
	{
		start = 0;
		end = 1;

		switch(mode) {
			case BOLD:
				start = line.find(bold);
				end = line.find(bold, start+1);
		
				if(start == std::string::npos) return 0;
				if(end < start) return 0;
			break;

			case ITALIC:
				start = line.find(italic);
				end = line.find(italic, start+1);

				if(start == std::string::npos) return 0;
				if(end < start) return 0;
			break;

			default:
			break;
		}
		return 1;
	}
	std::wstring between::add_boldtag(const std::wstring& line)
	{
		LinePos start, end;
		mark_pos(line, BOLD, start, end);

		const std::wstring tag_start = L"<b>";
		const std::wstring tag_end = L"</b>";

		std::wstring marked_line = line;
		
		marked_line.replace(start, 3, tag_start);
		marked_line.replace(end, 3, tag_end);

		return marked_line;
	}
	std::wstring between::add_italictag(const std::wstring& line)
	{
		LinePos start, end;
		mark_pos(line, ITALIC, start, end);

		const std::wstring tag_start = L"<i>";
		const std::wstring tag_end = L"</i>";

		std::wstring marked_line = line;

		marked_line.replace(start, 3, tag_start);
		marked_line.replace(end, 3, tag_end);

		return marked_line;
	}
// -------------------------------------------------------------------------------- 
} /* NameSpace Ln End */
// --------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	const std::locale loc;
	std::locale ja(loc, "ja_JP.utf8", std::locale::all);
	ja.global(loc);


	return 0;
}
