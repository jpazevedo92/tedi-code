@extends('layouts.layout')

@section('htmlheader_title')
	{{ trans('adminlte_lang::message.mpls_tag_edit') }}
@endsection

@section('box_title')
    {{ trans('adminlte_lang::message.mpls_tag_edit') }}
@endsection

@section('content')
	@include('forms.mpls_tag_form')
@endsection
