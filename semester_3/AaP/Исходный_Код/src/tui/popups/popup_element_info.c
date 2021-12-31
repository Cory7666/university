#include "__popups__.h"
#include "../forms/__forms__.h"

const menu_t PLACE_ELEMENT_MENU = {
    L"В начало",
    L"В конец",
    NULL
};

int tui_popup_edit_element_data (const wchar_t * title, list_data_t * edata, int create_new_element_mode)
{
    int
        exit_flag = 0,
        flags = TUI_AT_END_FLAG,
        selected_field = 1;
    wchar_t tmp_wcs[100];
    mkey_t key = MKEY_NULL;

    // Подготовка начальных данных
    if (create_new_element_mode)
    {
        memset (edata, 0, sizeof(list_data_t));
        edata->date.Y = 2021;
        edata->date.M = 11;
        edata->date.D = 11;
    }

    WINDOW * popup_win = newwin (22, 22 + ANIMAL_AREAL_MAX_LEN, 1, 1);
    PANEL  * popup_panel = new_panel (popup_win);
    update_panels ();

    tui_draw_popup_header (popup_win, title);
    
    do
    {
        /* Обработать нажатую клавишу */
        switch (key)
        {
            case MKEY_TAB:
                if (selected_field < 9 - (!create_new_element_mode))
                    selected_field++;
                else
                    selected_field = 1;
                break;
            
            case MKEY_ENTER:
                switch (selected_field)
                {
                    case 1:
                        memset (tmp_wcs, 0, sizeof(tmp_wcs));
                        if (edata->cage_num)
                            int2wcs (edata->cage_num, tmp_wcs);
                        tui_draw_popup_form (L"Ввод # Вольера", L"Введите номер вольера.", L"№", tmp_wcs, CAGE_NUM_DGT_CNT, VMASK_DIGITS);
                        edata->cage_num = wcs2int(tmp_wcs);
                        break;
                    case 2:
                        tui_draw_popup_date (L"Ввод даты поступления", L"Введите дату поступления животкого в центр.", &edata->date);
                        break;
                    case 3:
                        tui_draw_popup_form (L"Ввод ареала", L"Введите ареал обитания животного.", L"ареал", edata->animal.areal, ANIMAL_AREAL_MAX_LEN, VMASK_ANY_CHAR | VMASK_SPACES);
                        break;
                    case 4:
                        tui_draw_popup_form (L"Ввод породы", L"Введите породу животного.", L"порода", edata->animal.breed, ANIMAL_BREED_MAX_LEN, VMASK_ANY_CHAR | VMASK_SPACES);
                        break;
                    case 5:
                        tui_draw_popup_form (L"Ввод имени", L"Введите имя животного.", L"имя", edata->animal.name, ANIMAL_NAME_MAX_LEN, VMASK_ANY_CHAR | VMASK_SPACES);
                        break;
                    case 6:
                        tui_draw_popup_form (L"Ввод типа продукта", L"Введите тип продукта.", L"тип", edata->products.type, PRODUCT_TYPE_MAX_LEN, VMASK_ANY_CHAR | VMASK_SPACES);
                        break;
                    case 7:
                        memset (tmp_wcs, 0, sizeof(tmp_wcs));
                        if (edata->products.weight)
                            float2wcs (edata->products.weight, tmp_wcs);
                        tui_draw_popup_form (L"Ввод веса продукта", L"Введите вес продукта, употребляемого животным за день.", L"вес", tmp_wcs, WEIGHT_DGT_CNT, VMASK_DIGITS | VMASK_PUNCTS);
                        edata->products.weight = wcs2float(tmp_wcs);
                        break;
                    case 8:
                        memset (tmp_wcs, 0, sizeof(tmp_wcs));
                        if (edata->products.cost)
                            float2wcs (edata->products.cost, tmp_wcs);
                        tui_draw_popup_form (L"Ввод стоимости продукта", L"Введите стоимость всех продуктов, потребляемых животным за день", L"стоим", tmp_wcs, COST_DGT_CNT, VMASK_DIGITS | VMASK_PUNCTS);
                        edata->products.cost = wcs2float(tmp_wcs);
                        break;
                    case 9:
                        switch (tui_draw_popup_select (L"Выбрать размещение данных", L"Где разместить создаваемый элемент по отнашению к существующим данным?", PLACE_ELEMENT_MENU))
                        {
                            // Добавить в начало
                            case 1:
                                flags &= ~TUI_AT_END_FLAG;
                                flags |= TUI_AT_BEGIN_FLAG;
                                break;
                            // Добавить в конец списка
                            case 2:
                                flags &= ~TUI_AT_BEGIN_FLAG;
                                flags |= TUI_AT_END_FLAG;
                                break;
                        }
                        break;
                }
                break;
            
            case L'A': case L'a':
                flags |= TUI_ADD_ELEMENT_FLAG;
                exit_flag = 1;
                break;
            
            case L'E': case L'e':
                flags = TUI_ADD_ELEMENT_CACELLED;
                exit_flag = 1;
                break;
            
            default:
                break;
        }



        /* Отрисовать список */

        // Номер вольера
        memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (edata->cage_num) int2wcs (edata->cage_num, tmp_wcs);
        if (selected_field == 1) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 5, 1,  " Номер вольера    "); tui_draw_form_field (popup_win, 5, 21, L"НЕТ НОМ", tmp_wcs, 7);
        if (selected_field == 1) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);


        // Дата поступления
        memset (tmp_wcs, 0, sizeof(tmp_wcs)); date2wcs (&edata->date, tmp_wcs);
        if (selected_field == 2) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 6, 1,  " Дата поступления "); tui_draw_form_field (popup_win, 6, 21, L"НЕТ ДАТЫ", tmp_wcs, 10);
        if (selected_field == 2) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);



        mvwprintw (popup_win, 7, 1,  " О животном:      ");


        // Ареал обитания
        if (selected_field == 3) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 8, 1,  " * Ареал обитания "); tui_draw_form_field (popup_win, 8,  21, L"НЕТ АРЕАЛА", edata->animal.areal, ANIMAL_AREAL_MAX_LEN - 1);
        if (selected_field == 3) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);


        // Порода
        if (selected_field == 4) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 9, 1,  " * Порода         "); tui_draw_form_field (popup_win, 9,  21, L"НЕТ ПОРОДЫ", edata->animal.breed, ANIMAL_BREED_MAX_LEN - 1);
        if (selected_field == 4) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);


        // Имя
        if (selected_field == 5) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 10, 1, " * Имя            "); tui_draw_form_field (popup_win, 10, 21, L"НЕТ ИМЕНИ",  edata->animal.name,  ANIMAL_NAME_MAX_LEN  - 1);
        if (selected_field == 5) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);


        
        mvwprintw (popup_win, 11, 1, " О продуктах:     ");
        
        
        // Тип
        if (selected_field == 6) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 12, 1, " * Тип            "); tui_draw_form_field (popup_win, 12, 21, L"НЕТ ТИПА",   edata->products.type, PRODUCT_TYPE_MAX_LEN - 1);
        if (selected_field == 6) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);


        // Вес
        memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (edata->products.weight) float2wcs (edata->products.weight, tmp_wcs);
        if (selected_field == 7) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 13, 1, " * Вес            "); tui_draw_form_field (popup_win, 13, 21, L"НЕТ ВЕС", tmp_wcs, 7);
        if (selected_field == 7) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);

        
        // Стоимость
        memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (edata->products.cost) float2wcs (edata->products.cost, tmp_wcs);
        if (selected_field == 8) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        mvwprintw (popup_win, 14, 1, " * Стоимость      "); tui_draw_form_field (popup_win, 14, 21, L"НЕТ ЦЕН", tmp_wcs, 7);
        if (selected_field == 8) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        
        
        // Куда добавлять элемент - в начало или в конец
        if (create_new_element_mode)
        {
            if (selected_field == 9) wattron (popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
            mvwprintw (popup_win, 16, 1, " Добавить в       "); mvwprintw (popup_win, 16, 21, (flags & TUI_AT_BEGIN_FLAG) ? "В начало" : "В конец");
            if (selected_field == 9) wattroff(popup_win, TUI_HIGHLIGHT_ITEM_STYLE);
        }

        mvwprintw (popup_win, 18, 1, "[TAB] Навигация. [A] Сохранить. [E] Отменить.");

        update_panels ();
        doupdate ();

        key = getwchar ();
    }
    while (!exit_flag);



    del_panel (popup_panel);
    delwin (popup_win);
    return flags;
}

void tui_popup_show_only_element (const wchar_t * title, const list_elem_t * elem)
{
    wchar_t tmp_wcs[100];
    mkey_t key = MKEY_NULL;
    
    WINDOW * popup_win = newwin (23, 22 + ANIMAL_AREAL_MAX_LEN, 1, 1);
    PANEL  * popup_panel = new_panel (popup_win);
    update_panels ();

    tui_draw_popup_header (popup_win, title);
    
    
    /* Отрисовать список */

    // ID элемента
    memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (elem->id) int2wcs (elem->id, tmp_wcs);
    mvwprintw (popup_win, 5, 1,  " ID записи        "); tui_draw_form_field (popup_win, 5, 21, L"НЕТ ID", tmp_wcs, 7);

    // Номер вольера
    memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (elem->data.cage_num) int2wcs (elem->data.cage_num, tmp_wcs);
    mvwprintw (popup_win, 6, 1,  " Номер вольера    "); tui_draw_form_field (popup_win, 5, 21, L"НЕТ НОМ", tmp_wcs, 7);

    // Дата поступления
    memset (tmp_wcs, 0, sizeof(tmp_wcs)); date2wcs (&elem->data.date, tmp_wcs);
    mvwprintw (popup_win, 7, 1,  " Дата поступления "); tui_draw_form_field (popup_win, 6, 21, L"НЕТ ДАТЫ", tmp_wcs, 10);

    mvwprintw (popup_win, 8, 1,  " О животном:      ");

    // Ареал обитания
    mvwprintw (popup_win, 9, 1,  " * Ареал обитания "); tui_draw_form_field (popup_win, 8,  21, L"НЕТ АРЕАЛА", elem->data.animal.areal, ANIMAL_AREAL_MAX_LEN - 1);

    // Порода
    mvwprintw (popup_win, 10, 1,  " * Порода         "); tui_draw_form_field (popup_win, 9,  21, L"НЕТ ПОРОДЫ", elem->data.animal.breed, ANIMAL_BREED_MAX_LEN - 1);

    // Имя
    mvwprintw (popup_win, 11, 1, " * Имя            "); tui_draw_form_field (popup_win, 10, 21, L"НЕТ ИМЕНИ",  elem->data.animal.name,  ANIMAL_NAME_MAX_LEN  - 1);
        
    mvwprintw (popup_win, 12, 1, " О продуктах:     ");
        
    // Тип
    mvwprintw (popup_win, 13, 1, " * Тип            "); tui_draw_form_field (popup_win, 12, 21, L"НЕТ ТИПА",   elem->data.products.type, PRODUCT_TYPE_MAX_LEN - 1);

    // Вес
    memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (elem->data.products.weight) float2wcs (elem->data.products.weight, tmp_wcs);
    mvwprintw (popup_win, 14, 1, " * Вес            "); tui_draw_form_field (popup_win, 13, 21, L"НЕТ ВЕС", tmp_wcs, 7);
        
    // Стоимость
    memset (tmp_wcs, 0, sizeof(tmp_wcs)); if (elem->data.products.cost) float2wcs (elem->data.products.cost, tmp_wcs);
    mvwprintw (popup_win, 15, 1, " * Стоимость      "); tui_draw_form_field (popup_win, 14, 21, L"НЕТ ЦЕН", tmp_wcs, 7);

    mvwprintw (popup_win, 19, 1, "[E] Выйти.");

    update_panels ();
    doupdate ();

    while ((key = getwchar ()) != L'E' && key != L'e');



    del_panel (popup_panel);
    delwin (popup_win);
    return;
}