%define RELEASE 0
%define MAJOR 1
%define MINOR 0

Name: configuration-library
Version: %{RELEASE}.%{MAJOR}.%{MINOR}
Release: 1%{?dist}
Summary: configuration library 


Group: Development/Libraries
License: MIT License
URL: 
Source0: 
BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)


%description
Add a description here
This package provides a wrapper around jsoncpp.  The wrapper exposes Apache Qpid Variant Map type data 
originating from JSON formatted text files.  


%prep
%setup -q


%build
cmake .
make all


%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{_libdir}
mkdir -p %{buildroot}%{_includedir}/namespace
#cp main %{buildroot}/namespace
#cp *.so %{buildroot}%{_libdir}
#cp -a include/* %{buildroot}%{_includedir}/namespace

%check
make test

%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%dir %{_includedir}/namespace
%{_includedir}/namespace/*.h
%{_libdir}/*.so


%changelog
* Thu Jan 24 2013 Daniel Feren <daniel.feren@redhat.com> - 0.1.0
- Initial release
