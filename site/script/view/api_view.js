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
	_accordionMenuClickHandler: function(evt) {
		var view = this;
		var parentView = view.get('parentView');
		var menuItemId = $(evt.target).attr('id');
		
		if (menuItemId === this.get('_currentMenuItem')) {
			view._setupAccordionMenu();
			parentView._updateContentViewTemplate('uml');
			view.set('_currentMenuItem', 'uml');
		} else {
        
        	view._updateAccordionMenu(menuItemId);
        
			parentView._updateContentViewTemplate(menuItemId);
			view.set('_currentMenuItem', menuItemId);
		}
	},
	_updateAccordionMenu: function(menuItemId) {
		var parts = menuItemId.split('-');

		if (parts.length === 1) {
			var menuItem = parts[0];		

			var target = $('#' + parts[0]);
			$(target).next('div').siblings('div').slideUp();
        	$(target).siblings('a').css('color', '#6d6e70');
        	$(target).next('div').slideToggle();
        	$(target).css('color', '#00979C');
		} else {
			var target = $('#' + menuItemId);
			$(target).css('color', '#00979C');
		}		
	}
});

Application.ApiContent = Ember.View.extend({
	templateName: 'uml',
	updateTemplate: function(templateName) {
		console.log(templateName);
		var view = this;
		view.set('templateName', templateName);
		view.rerender();
	}
});

Application.ApiView = Ember.View.extend({
	menu: Application.ApiMenu,
	content: Application.ApiContent,
	_updateContentViewTemplate: function(templateName) {
		var view = this;

		var contentView = view.get('contentViewInstance');
		contentView.updateTemplate(templateName);
	}	
});