Application.ApiView = Ember.View.extend({
	didInsertElement: function() {
		var view = this;
		var name = view.get('templateName');
		name = name.split(/\s*\-\s*/g)[0];

		$('#index a').next('div').siblings('div').slideUp();

		var target = $('#' + name);	
		$(target).next('div').siblings('div').slideUp();
        $(target).siblings('a').css('color', '#6d6e70');
        $(target).next('div').slideToggle();
        $(target).css('color', '#00979C');
	},
	layoutName: 'api',
	templateName: 'uml',
	actions: {
		menuSelection: function(name) {
			var view = this;
			view.set('templateName', name);
			view.rerender();
		}
	},	
});