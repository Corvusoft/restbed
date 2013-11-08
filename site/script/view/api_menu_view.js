Application.ApiMenu = Ember.View.extend({
    templateName: 'api-menu',
    _currentMenuItem: undefined,
    didInsertElement: function () {
        var view = this;
        view._setupAccordionMenu();
    },
    click: function(evt) {
        var view = this;
        view._accordionMenuClickHandler(evt);
    },
    _setupAccordionMenu: function() {
        $('#index a').next('div').siblings('div').slideUp();
    },
    _isMainMenuOption: function(menuItemId) { //option
        return (menuItemId.split('-').length == 1)
    },
    _accordionMenuClickHandler: function(evt) {
        var view = this;
        var parentView = view.get('parentView');
        var menuOptionId = $(evt.target).attr('id');

        if (menuOptionId === view.get('_currentMenuItem') && view._isMainMenuOption(menuOptionId)) {
            view._setupAccordionMenu();
            parentView._updateContentViewTemplate('uml');
            view.set('_currentMenuItem', 'uml');
        } else {
            view._updateAccordionMenu(menuOptionId);

            parentView._updateContentViewTemplate(menuOptionId);

            if(view._isMainMenuOption(menuOptionId)) {
                view.set('_currentMenuItem', menuOptionId);
            }
        }
    },
    _updateAccordionMenu: function(menuOptionId) {
        var parts = menuOptionId.split('-');

        if (parts.length === 1) {
            var menuItem = parts[0];

            var target = $('#' + parts[0]);
            $(target).next('div').siblings('div').slideUp();
            $(target).siblings('a').css('color', '#6d6e70');
            $(target).next('div').slideToggle();
            $(target).css('color', '#00979C');
        } else {
            var target = $('#' + menuOptionId);
            $(target).css('color', '#00979C');
        }
    }
});
